

import argparse
from llm import ask_llm
from pathlib import Path
import random
import re
import os
import json
from multiprocessing import Process, Queue
from tqdm import tqdm

MODEL_VERSION = None


def parse_args():
  parser = argparse.ArgumentParser(description="Process some features.")
  parser.add_argument('--model', choices=['dpsk-v3', 'claude', 'dpsk-r1'],
                      help="Choose the LLM model to use: 'dpsk-v3', 'dpsk-r1', or 'claude'")

  mode_subparsers = parser.add_subparsers(
    dest='mode',
    help='What are you going to do?',
    required=True
  )

  parser_generate = mode_subparsers.add_parser('generate')
  parser_generate.add_argument(
    '--amount', choices=['example', 'many', 'all'], default='random',
    help="Choose 'random' to randomly select a built-in program description, or 'example' to use a specific example feature documentation."
  )
  parser_generate.add_argument(
    '--dir', default=None,
  )
  parser_generate.add_argument(
    '--input', type=str, default=None,
    help="Enter program description."
  )
  parser_generate.add_argument(
    '--c_output', default=None, help='Output c-file name.')
  parser_generate.add_argument(
    '--bsc_output', default=None, help='Output bsc-file name.')

  parser_translate = mode_subparsers.add_parser('translate')
  parser_translate.add_argument(
    '-i', '--input', default='input_c.c', help='Input file name.')
  parser_translate.add_argument(
    '-o', '--output', default='output_cbs.cbs', help='Output file name.')

  args = parser.parse_args()
  global MODEL_VERSION
  MODEL_VERSION = args.model
  print("Model is set to:", MODEL_VERSION)
  return args


def generate_worker(input_q: Queue, output_q: Queue):
  for idx, dir_name, program_desc in iter(input_q.get, None):
    generate(
      dir_name=dir_name,
      c_output=Path(f'programs/{dir_name}/c_{idx}.c'),
      bsc_output=Path(f'programs/{dir_name}/cbs_{idx}.cbs'),
      doc=Path(f'docs/{dir_name}.md'),
      program_description=program_desc,
    )
    output_q.put((idx))


def generate_many(
  dir_name: str,
  programs_desc: list,
  worker_count=os.cpu_count(),
):
  task_queue = Queue()
  done_queue = Queue()
  for _ in range(worker_count):
    Process(target=generate_worker, args=(task_queue, done_queue)).start()
  for idx, program_desc in enumerate(programs_desc):
    task_queue.put((idx, dir_name, program_desc))
  for _ in range(worker_count):
    task_queue.put(None)
  for _ in tqdm(range(len(programs_desc)), desc=f'Generating for {dir_name}'):
    _ = done_queue.get()


def generate(
  *,
  dir_name: str,
  c_output: Path,
  bsc_output: Path,
  doc: Path,
  program_description: str,
):
  with doc.open("r", encoding="utf-8") as f:
    feature_content = f.read()
  feature_name = doc.name

  if program_description is None:
    program_description = "Any program is ok."

  system_prompt, user_prompt = build_prompt(
    dir_name=dir_name,
    feature_content=feature_content,
    program_description=program_description,
  )

  # Call the LLM to generate the C and Bisheng-C code
  response = ask_llm(system_prompt=system_prompt,
                     user_prompt=user_prompt, model_version=MODEL_VERSION)

  # Preprocess response to extract JSON if wrapped in code block
  json_pattern = r"```(?:json)?\s*(.*?)\s*```"
  match = re.search(json_pattern, response, re.DOTALL | re.IGNORECASE)
  if match:
    response = match.group(1).strip()

  try:
    response = json.loads(response)
  except Exception as e:
    print(f"Failed to parse LLM response: {e}")
    return

  if not c_output.exists():
    c_output.parent.mkdir(parents=True, exist_ok=True)
  with open(c_output, 'w', encoding='utf-8') as f:
    f.write("/*\n" + feature_name + "\n" +
            program_description + '\n*/\n' + response['c_code'])
  if not bsc_output.exists():
    bsc_output.parent.mkdir(parents=True, exist_ok=True)
  with open(bsc_output, 'w', encoding='utf-8') as f:
    f.write("/*\n" + feature_name + "\n" + program_description +
            '\n*/\n' + response['bisheng_c_code'])


def build_prompt(
  dir_name: str,
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  if dir_name == '6_内存安全':
    return build_prompt_memory_safety(
      feature_content=feature_content,
      program_description=program_description,
    )
  elif dir_name == '7_owned-struct-类型':
    return build_prompt_owned_struct(
      feature_content=feature_content,
      program_description=program_description,
    )
  elif dir_name == '9_非空指针':
    return build_prompt_nonnull_pointer(
      feature_content=feature_content,
      program_description=program_description,
    )
  elif dir_name == '10_标准库':
    return build_prompt_standard_lib(
      feature_content=feature_content,
      program_description=program_description,
    )
  else:
    return build_prompt_generic(
      feature_content=feature_content,
      program_description=program_description,
    )


def build_prompt_memory_safety(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  # TODO: Implement a more specific prompt for memory safety
  # i.e. do not use the generic prompt
  return build_prompt_generic(
    feature_content=feature_content,
    program_description=program_description,
  )


def build_prompt_owned_struct(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  '''
  feature_content: The content of the feature documentation.
  program_description: A description of the program to be generated.
  Returns a tuple of system and user prompts.
  '''

  # One-shot example
  one_shot_example = "[\n"
  "  {\n"
  "    \"description\": \"...\",\n"
  "    \"c_code\": \"...\",\n"
  "    \"bisheng_c_code\": \"...\n"
  "  }\n"
  "]\n"

  # System prompt
  system_prompt = "You are an expert in both C and Bisheng-C programming languages. " \
      "Bisheng C adopts a different strategy. It incorporates many enhanced designs based on the " \
      "C language, such as stronger memory safety features and built-in support for concurrency. " \
      "Moreover, these features can be incrementally adopted in existing codebases without requiring " \
      "a full rewrite of legacy code. It can be said that Bisheng C is a superset of the C language."

  # User prompt
  user_prompt = f"""
  First, you need to write some simple C language programs, then use the new features of Bisheng C you have learned to translate the C programs into Bisheng C code, ensuring that the differences between the two are highlighted and that their outputs are completely identical.

  Requirements:
  - {program_description}
  - Return the result in JSON format, containing three fields: description, c_code, and bisheng_c_code.
  - Note: The outputs of both programs must be identical. Ensure there are no extra outputs (such as additional logs, debug info, or unintended formatting) in either program.
  
  Notice:
  - You also need to use 'include<>' statements in the bisheng-C code, such as <stdio.h> and <stdlib.h>.
  - The member function of an object does not need to explicitly pass the object's own reference as the first parameter, but this parameter must be named this. For example:
    'bool struct CircularBuffer<T>::pop(struct CircularBuffer<T> *this, T *item)' When calling it, you can simply use `int_buffer.pop(&val)` instead of `int_buffer.pop(&int_buffer, &val)`. Some other example:
    - It is 'future->free()' rather than 'future->free(future)'.
    - It is 'future->poll()' rather than 'future->poll(future)'.
    - It is 'result.is_completed(&value)' rather than 'result.is_completed(&result, &value)'.
  - Cast to (void * owned) before passing a pointer to a function that takes an owned pointer, such as 'safe_malloc<Type>(...)', 'safe_free', etc. For example:
    - safe_free((void * owned)q);
  - Include "bishengc_safety.hbs" before use "safe_malloc", "safe_free", etc. in Bisheng-C code.
  - No need to set pointer to NULL after the ownership transfer, such as 'q = NULL;'. In Bisheng-C, the ownership transfer is implicit and does not require explicit nullification.
  - You need to include <stdlib.h> before using the 'async' keyword if you use it.
  - Bi-Sheng-C has added some header files with the .hbs extension, but do not rename the original C header files to .hbs.
  - There is no bool type in C, so you can use int instead. In Bisheng-C, you can use _Bool type.
  - 'async' can not be used to decorate 'main' function in Bisheng-C.

  - No need to write 'printf' in the destructor, make sure the outputs of both the standard C program and the Bi-Sheng-C program are identical.
  - In Bisheng-C, member functions of an owned struct require an explicit this parameter in their definition (e.g., Type *this), but when calling these functions, the this parameter is implicitly passed, allowing calls like object.function() instead of object.function(&object).
  - Use the keyword "owned struct" to define custom types instead of "struct". Ensure the type name follows the "owned struct" declaration.
  - Member functions must explicitly declare the `this` parameter with compatible pointer types, such as `C*`, `const C*`, or `C* owned`.
  - Define destructors with the `~` prefix and only allow a single destructor per `owned struct`. The destructor must accept one parameter that is the same type as the `owned struct`.
  - Owned pointers in members must be manually released in the destructor using functions like `safe_free()`. Ensure you include "bishengc_safety.hbs" to use `safe_malloc` and `safe_free`.
  - Member variables default to `private` visibility in an `owned struct`. You must explicitly specify `public` to allow external access.
  - When creating instances of an `owned struct`, use struct initializer syntax and ensure all members are fully initialized. If members are owned pointers, they must be allocated properly.
  - Do not define generic functions inside an `owned struct`. Always keep function definitions outside of the `owned struct` if generics are needed.
  - Ensure that `owned struct` instances are either in `owned` or `moved` state when they go out of scope; otherwise, handle the potential error of "partially moved owned struct".
  - The destructor is called automatically at the end of the object’s lifecycle. If you have owned pointers, ensure they are freed in the destructor to avoid memory leaks.
  - Destructors for `owned struct` types must not be called manually, and their invocation order is vital: outer destructors are called before inner member destructors.
  - Avoid using static variables within the destructor, as global or static destructors will not execute as expected.

  {one_shot_example}

  Below is a documentation excerpt describing some features of Bisheng-C:
    {feature_content}
  """
  return system_prompt, user_prompt


def build_prompt_nonnull_pointer(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  # TODO: Implement a more specific prompt for nonnull pointers
  # i.e. do not use the generic prompt
  return build_prompt_generic(
    feature_content=feature_content,
    program_description=program_description,
  )


def build_prompt_standard_lib(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  '''
  A specific prompt generator for the "standard library" feature category in BiSheng-C.
  '''

  # One-shot example
  one_shot_example = """
[
  {
    "description": "...",
    "c_code": "...",
    "bisheng_c_code": "..."
  }
]
"""

  # System prompt
  system_prompt = """
  You are an expert in both standard C and BiSheng-C. 
  BiSheng-C is a memory-safe, ownership-enforcing extension of C, supporting safe/unsafe zones and high-level types 
  such as Vec, Option, Rc, RefCell, and HashMap. Your job is to write **minimal and compilable** BiSheng-C programs 
  that demonstrate how BiSheng-C features differ from C, while strictly following safety rules.

  ✅ BiSheng-C DOs:
  - Wrap unsafe calls (e.g., `printf`, `String::from`) using `unsafe {}` syntax
  - Use `#include \"xxx.hbs\"` for BiSheng-C-specific types (e.g., \"vec.hbs\", \"string.hbs\")
  - Use `safe int main(void)` — not `int main()`
  - Use `_Bool` instead of `bool`
  - Free owned memory via `safe_free((void * owned)x);` — only for malloc'ed pointers

  ❌ BiSheng-C DON'Ts:
  - Never use `++`, `--`, or `arr[i]` style indexing on owned types
  - Never call unsafe functions in safe blocks (e.g., `printf`, `String::from`, `fopen`)
  - Never write `use Vec;`, `use String;` — not supported
  - Never `#include \"stdio.hbs\"` — use `<stdio.h>` instead
  - Never cast or free complex types like `String`, `Rc<T>` via `(void * owned)` — will cause error
  - Never mutate while borrowed, obey the borrow checker

  Your output must **compile in BiSheng-C** without warnings or errors — or it is invalid.
  """

  # User prompt
  user_prompt = f"""
  You need to write two extremely simple programs to demonstrate how the following feature makes BiSheng-C different from standard C.

  Your task:

  - Write two minimal programs (as simple as possible) that fulfill this requirement:
    - {program_description}

  - The output of the two programs **must be identical**. No extra debug logs, print statements, or formatting should be present.

  Output format:

  Return your result in JSON format, containing exactly three fields:
  - \"description\": (Explain how this feature makes BiSheng-C different from standard C)
  - \"c_code\": (C version of the program)
  - \"bisheng_c_code\": (BiSheng-C version of the program)

  BiSheng-C Code Requirements:

  1. 🚫 Never call unsafe functions (e.g., `printf`, `String::from`, `HashMap::insert`, `fopen`) directly in `safe` functions.
    - ✅ Use `unsafe {{ printf(...) }}` or `log_safe_*()` if available.

  2. ✅ Always use `#include <...>` for C standard headers, and `#include \"xxx.hbs\"` for BiSheng-C specific features.
  3. ✅ When using `safe_malloc`, `safe_free`, `forget`, etc., include `\"bishengc_safety.hbs\"`.
  4. ✅ Always write `safe int main(void)` — not `main()` with empty params.
  5. 🚫 Do not use `++` / `--` operators. Use `i = i + 1` instead.
  6. 🚫 Do not index into owned pointers like `arr[0]`. Use `Vec` or `.deref()` accessors.
  7. ✅ When passing owned pointers, cast explicitly as `(void * owned)` before freeing.
  8. ✅ Never nullify after ownership transfer — BiSheng-C tracks ownership statically.
  9. 🚫 Avoid memory leaks — owned values must be freed or transferred before discard.
  10. 🚫 Never mutate a value while it is immutably borrowed. Obey borrow checker rules.
  11. ✅ When using types like `Vec<String>`, `Option<T>`, or `Rc<T>`:
      - Include the proper `.hbs` file (e.g., \"vec.hbs\", \"option.hbs\")
      - 🚫 Do NOT use `use Vec;`, `use String;` — these are not supported in BiSheng-C
  12. ✅ Use `_Bool` instead of `bool` in BiSheng-C.
  13. 🚫 Do not make `main()` an async function. Avoid blocking calls like `Scheduler::run()` before `destroy()`.

  💡 Recommended:
  - For output, prefer `log_safe_int`, `log_safe_str`, etc., if your system defines them.
  - Always use `unsafe {{ ... }}` to isolate unsafe operations like `String::from(\"hello\")`.

  ❌ Forbidden patterns (will cause compile-time failure in BiSheng-C):
  - Implicit string literal usage (`String::from(\"abc\")`) in safe zones
  - Owned pointer indexing (`arr[i]`)
  - `++`, `--`, or C-style unsafe loops
  - `use Vec;`, `use String;`
  - `#include \"stdio.hbs\"` — use `<stdio.h>` instead
  - Redefining built-in functions like `safe_swap`, `forget`

  {one_shot_example}

  Below is a documentation excerpt describing some features of BiSheng-C:
  {feature_content}
  """

  return system_prompt, user_prompt



def build_prompt_generic(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  '''
  feature_content: The content of the feature documentation.
  program_description: A description of the program to be generated.
  Returns a tuple of system and user prompts.
  '''

  # One-shot example
  one_shot_example = "[\n"
  "  {\n"
  "    \"description\": \"...\",\n"
  "    \"c_code\": \"...\",\n"
  "    \"bisheng_c_code\": \"...\n"
  "  }\n"
  "]\n"

  # System prompt
  system_prompt = "You are an expert in both C and Bisheng-C programming languages. " \
      "Bisheng C adopts a different strategy. It incorporates many enhanced designs based on the " \
      "C language, such as stronger memory safety features and built-in support for concurrency. " \
      "Moreover, these features can be incrementally adopted in existing codebases without requiring " \
      "a full rewrite of legacy code. It can be said that Bisheng C is a superset of the C language."

  # User prompt
  user_prompt = f"""
  You need to write two simple (as simple as possible) programs that demonstrate how below features described above make Bisheng-C different from standard C.

  Requirements:
  - {program_description}
  - Return the result in JSON format, containing three fields: description, c_code, and bisheng_c_code.
  - Note: The outputs of both programs must be identical. Ensure there are no extra outputs (such as additional logs, debug info, or unintended formatting) in either program.
  
  Notice:
  - You also need to use 'include<>' statements in the bisheng-C code, such as <stdio.h> and <stdlib.h>.
  - The member function of an object does not need to explicitly pass the object's own reference as the first parameter, but this parameter must be named this. For example:
    'bool struct CircularBuffer<T>::pop(struct CircularBuffer<T> *this, T *item)' When calling it, you can simply use `int_buffer.pop(&val)` instead of `int_buffer.pop(&int_buffer, &val)`. Some other example:
    - It is 'future->free()' rather than 'future->free(future)'.
    - It is 'future->poll()' rather than 'future->poll(future)'.
    - It is 'result.is_completed(&value)' rather than 'result.is_completed(&result, &value)'.
  - Cast to (void * owned) before passing a pointer to a function that takes an owned pointer, such as 'safe_malloc<Type>(...)', 'safe_free', etc. For example:
    - safe_free((void * owned)q);
  - Include "bishengc_safety.hbs" before use "safe_malloc", "safe_free", etc. in Bisheng-C code.
  - No need to set pointer to NULL after the ownership transfer, such as 'q = NULL;'. In Bisheng-C, the ownership transfer is implicit and does not require explicit nullification.
  - You need to include <stdlib.h> before using the 'async' keyword if you use it.
  - Bi-Sheng-C has added some header files with the .hbs extension, but do not rename the original C header files to .hbs.
  - There is no bool type in C, so you can use int instead. In Bisheng-C, you can use _Bool type.
  - 'async' can not be used to decorate 'main' function in Bisheng-C.

  {one_shot_example}

  Below is a documentation excerpt describing some features of Bisheng-C:
    {feature_content}
  """
  return system_prompt, user_prompt


def translate(
  input_file: Path,
  output_file: Path,
):
  raise NotImplementedError(
    "Translation functionality is not implemented yet.")


def main():
  args = parse_args()

  if args.mode == 'generate':
    if args.amount == 'many':
      if args.dir is None:
        raise ValueError("When amount is 'many', dir must be specified.")
      dir_name = args.dir
      programs_desc = Path(f'program_desc/{dir_name}.json')
      desc = json.loads(programs_desc.read_text(encoding='utf-8'))
      generate_many(
        dir_name=dir_name,
        programs_desc=desc,
      )
    elif args.amount == 'all':
      from const import lang_sub_ft
      for sub_ft in lang_sub_ft:
        dir_name = sub_ft
        programs_desc = Path(f'program_desc/{dir_name}.json')
        desc = json.loads(programs_desc.read_text(encoding='utf-8'))
        generate_many(
          dir_name=dir_name,
          programs_desc=desc,
        )
    else:
      if args.c_output is None:
        args.c_output = f'programs/{args.amount}.c'
      if args.bsc_output is None:
        args.bsc_output = f'programs/{args.amount}.cbs'
  elif args.mode == 'translate':
    # TODO: Implement translation functionality
    translate()
  else:
    print("Invalid mode. Use 'generate' or 'translate'.")


if __name__ == "__main__":
  main()