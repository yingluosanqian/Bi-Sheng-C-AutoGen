

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
      dir_name,
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
  return build_prompt_memory_safety(
    feature_content=feature_content,
    program_description=program_description,
  )


def build_prompt_owned_struct(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  # TODO: Implement a more specific prompt for owned-struct type
  # i.e. do not use the generic prompt
  return build_prompt_memory_safety(
    feature_content=feature_content,
    program_description=program_description,
  )


def build_prompt_nonnull_pointer(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  # TODO: Implement a more specific prompt for nonnull pointers
  # i.e. do not use the generic prompt
  return build_prompt_memory_safety(
    feature_content=feature_content,
    program_description=program_description,
  )


def build_prompt_standard_lib(
  feature_content: str,
  program_description: str,
) -> tuple[str, str]:
  # TODO: Implement a more specific prompt for standard library
  # i.e. do not use the generic prompt
  return build_prompt_memory_safety(
    feature_content=feature_content,
    program_description=program_description,
  )


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
