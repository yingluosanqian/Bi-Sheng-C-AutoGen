from pathlib import Path
from langchain.chat_models import init_chat_model
from langchain_core.output_parsers import JsonOutputParser
from langchain_core.prompts import PromptTemplate
from pydantic import BaseModel, Field

import utils
from utils import LangSubFeature, load_txt, save_txt
from valiadation import validate
from typing import Optional
import argparse
from tqdm import tqdm
from multiprocessing import Process, Queue
import os
import logging
logger = logging.getLogger(__name__)


class Code(BaseModel):
  code: str = Field(description="The code to be translated.")


def translate_generic(
  c_path: Path,
  feature: LangSubFeature,
  saved_path: Path,
):
  model = init_chat_model("deepseek-chat")

  examples_prompt = ""
  if feature.examples_code is not None:
    examples_prompt = "Here is some bisheng-c example:\n"
    for idx, example in enumerate(feature.examples_code):
      examples_prompt += f"Example {idx + 1}:\n{example}\n"

  query = f"""
Translate the following C or BiSheng-C code into BiSheng-C code with feature '{feature}':

{load_txt(c_path)}

Here is the introduction of BiSheng-C language:

{utils.BiShengCIntro}

Notice:
{feature.notes}

{examples_prompt}

Here is the feature '{feature}' description:

{feature.description}
  """

  # print("Query:\n", query)
  # print()

  parser = JsonOutputParser(pydantic_object=Code)
  prompt = PromptTemplate(
    template="Answer the user query.\n{format_instructions}\n{query}\n",
    input_variables=["query"],
    partial_variables={
      "format_instructions": parser.get_format_instructions()},
  )
  chain = prompt | model | parser
  resp = chain.invoke({"query": query})
  save_txt(saved_path, resp["code"])


#############################################################################
# Translate Single File
#############################################################################
def translate_single(
  c_code_fp: Path,
  feature: LangSubFeature,
  bsc_code_fp: Path,
  print_flag: bool = True,
) -> bool:
  if print_flag:
    print(f"{utils.BLUE}Translating single file: {c_code_fp.name} with feature '{feature.name}'{utils.RESET}")
  translate_generic(
    c_code_fp,
    feature,
    bsc_code_fp,
  )
  if print_flag:
    print(f"{utils.BLUE}Output saved to: {bsc_code_fp}{utils.RESET}")
  if validate(c_code_fp, bsc_code_fp):
    if print_flag:
      print(
        f"{utils.GREEN}[Success] Validation successful: C code and BiSheng-C code outputs match.{utils.RESET}")
    return True
  else:
    if print_flag:
      print(
        f"{utils.RED}[Failed] Validation failed: C code and BiSheng-C code outputs do not match.{utils.RESET}")
    return False


#############################################################################
# Translate Batch Files
#############################################################################
def translate_worker(input_q: Queue, output_q: Queue):
  for args in iter(input_q.get, None):
    output_q.put(translate_single(*args))


def translate_batch(
  input_dir: Path,
  feature: LangSubFeature,
  output_dir: Path,
):
  input_files = list(Path(input_dir).rglob("*.c"))
  num_of_files = len(input_files)
  print(f"{utils.BLUE}Translating all {utils.GREEN}{num_of_files}{utils.BLUE} files in directory: {input_dir} with feature '{feature.name}'{utils.RESET}")
  task_queue = Queue()
  done_queue = Queue()
  for _ in range(utils.worker_count):
    Process(target=translate_worker, args=(task_queue, done_queue)).start()
  for c_code_fp in input_files:
    bsc_code_fp = output_dir / Path(f"{c_code_fp.stem}.cbs")
    task_queue.put((c_code_fp, feature, bsc_code_fp, False))
  for _ in range(utils.worker_count):
    task_queue.put(None)
  success_count = 0
  with tqdm(total=len(input_files), desc="Translating C code to BiSheng-C") as p_bar:
    for idx in range(len(input_files)):
      result = done_queue.get()
      success_count += 1 if result else 0
      p_bar.update(1)
      p_bar.set_postfix({
        "success": f"{success_count}/{idx + 1} ({success_count / (idx + 1) * 100:.1f}%)"
      })
  print(f"{utils.GREEN}{success_count} out of {len(input_files)} C codes translated successfully. Rate: {success_count / len(input_files) * 100:.2f}%{utils.RESET}")
  print(f"{utils.BLUE}Output saved to: {output_dir}{utils.RESET}")


def main():
  parser = argparse.ArgumentParser(
    description="Translate C code to BiSheng-C code.")

  parser.add_argument("-m", "--mode", choices=["single", "batch"], default="single",
                      help="Run in 'single' (translate one file) or 'batch' (translate a directory) mode.")
  parser.add_argument("-i", "--input", type=str, required=True,
                      help="The input C code file path or directory.")
  parser.add_argument("-o", "--output", type=str, default=None,
                      help="The output BiSheng-C code file path or directory.")
  parser.add_argument("-f", "--feature", type=str, required=True,
                      choices=[feat.name for feat in utils.LSF_list],
                      help="The feature to be used for translation.")
  args = parser.parse_args()

  feature = None
  for feat in utils.LSF_list:
    if feat.name == args.feature:
      feature = feat
      break

  args.input = Path(args.input)
  if args.mode == "single":
    if args.output is None:
      args.output = utils.generated_code_dir / "default_output.cbs"
    args.output = Path(args.output)
    if not args.output.parent.exists():
      os.makedirs(args.output.parent)
    translate_single(
      args.input,
      feature,
      args.output,
    )
  else:
    if args.output is None:
      args.output = utils.generated_code_dir / "default_output_dir"
    args.output = Path(args.output)
    if not args.output.exists():
      os.makedirs(args.output)
    translate_batch(
      args.input,
      feature,
      args.output,
    )


if __name__ == "__main__":
  logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
    filename='app.log'
  )
  main()
