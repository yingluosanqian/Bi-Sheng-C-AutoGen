

import argparse
from dpsk_llm import ask_llm
from pathlib import Path
import random
import re
import json


def parse_args():
  parser = argparse.ArgumentParser(description="Process some features.")
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
  return parser.parse_args()


def generate_many(
  programs_desc: Path,
):
  for idx, program_desc in enumerate(programs_desc):
    generate(
      c_output=Path(f'programs/1_泛型/c_{idx}.c'),
      bsc_output=Path(f'programs/1_泛型/cbs_{idx}.cbs'),
      doc=Path('docs/1_泛型.md'),
      program_description=program_desc,
    )


def generate(
  *,
  c_output: Path,
  bsc_output: Path,
  doc: Path,
  program_description: str,
):
  print("Generating both C and Bisheng-C code...")
  with doc.open("r", encoding="utf-8") as f:
    feature_content = f.read()
  feature_name = doc.name

  if program_description is None:
    program_description = "Any program is ok."

  # print(f"Selected feature documentation: {sub_feature_content}")

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
  user_prompt = f"""Below is a documentation excerpt describing some features of Bisheng-C:
  {feature_content}

  You need to write two programs that demonstrate how the features described above make Bisheng-C different from standard C.

  Requirements:
  - {program_description}
  - one in C (file extension .c), and one in Bisheng-C (file extension .cbs).
  - The structure of c_code and bisheng_c_code should be similar, but they do not have to be exactly symmetrical. The main requirement is that their functionality and output are the same.
  - Return the result in JSON format, containing three fields: description, c_code, and bisheng_c_code.

  Notice:
  - You also need to use 'include<>' statements in the bisheng-C code, such as <stdio.h> and <stdlib.h>.
  - Had better to put a '\n' at the end of the output of C code and Bisheng-C code.
  - The member function of an object does not need to explicitly pass the object's own reference as the first parameter, but this parameter must be named this. For example:
    'bool struct CircularBuffer<T>::pop(struct CircularBuffer<T> *this, T *item)' When calling it, you can simply use `int_buffer.pop(&val)` instead of `int_buffer.pop(&int_buffer, &val)`.

  {one_shot_example}
  """

  # Call the LLM to generate the C and Bisheng-C code
  response = ask_llm(system_prompt=system_prompt, user_prompt=user_prompt)

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

  print(
    f"Success, saved C code to {c_output}, Bisheng-C code to {bsc_output}.")


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
      programs_desc = Path('program_desc/1_泛型.json')
      desc = json.loads(programs_desc.read_text(encoding='utf-8'))
      generate_many(
        programs_desc=desc
      )
    else:
      if args.c_output is None:
        args.c_output = f'programs/{args.amount}.c'
      if args.bsc_output is None:
        args.bsc_output = f'programs/{args.amount}.cbs'
      # generate(
      #   c_output=Path(args.c_output),
      #   bsc_output=Path(args.bsc_output),
      #   example=True if args.amount == 'example' else False,
      #   program_description=args.input
      # )
  elif args.mode == 'translate':
    # TODO: Implement translation functionality
    translate()
  else:
    print("Invalid mode. Use 'generate' or 'translate'.")


if __name__ == "__main__":
  main()
