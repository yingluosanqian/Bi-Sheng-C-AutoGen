from pathlib import Path
from langchain.chat_models import init_chat_model
from langchain_core.messages import HumanMessage, SystemMessage
from langchain_core.output_parsers import JsonOutputParser
from langchain_core.prompts import PromptTemplate
from pydantic import BaseModel, Field

import utils
from utils import LangSubFeature, load_txt, save_txt
from valiadation import validate
from typing import Optional
import argparse
from tqdm import tqdm


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


def test():
  example_path = Path("test_programs/0_成员函数/c_0.c")
  saved_path = Path("temp.cbs")
  translate_generic(
    example_path,
    utils.LSFMemberFunction,
    saved_path,
  )


def test_many(
  feature: LangSubFeature,
  num: Optional[int] = None,
):
  test_dir = Path("test")
  if not test_dir.exists():
    test_dir.mkdir(parents=True, exist_ok=True)
  c_codes_fp = feature.test_programs_fp([utils.CodeSuffix.C])

  if num is not None:
    c_codes_fp = c_codes_fp[:num]

  success_count = 0
  with tqdm(total=len(c_codes_fp), desc="Translating C code to BiSheng-C") as p_bar:
    for idx, c_code_fp in enumerate(c_codes_fp):
      bsc_code_fp = test_dir / Path(f"temp_{c_code_fp.stem}.cbs")
      translate_generic(
        c_code_fp,
        feature,
        bsc_code_fp,
      )
      if validate(c_code_fp, bsc_code_fp):
        success_count += 1
      p_bar.update(1)
      p_bar.set_postfix({
        "rate": f"{success_count}/{idx + 1}, {success_count / (idx + 1) * 100:.2f}%"
      })
  print(f"Success count: {success_count}, total count: {len(c_codes_fp)}")
  print("Success rate:", success_count / len(c_codes_fp) * 100, "%")


def main():
  parser = argparse.ArgumentParser(
    description="Translate C code to BiSheng-C code.")
  parser.add_argument(
    "--feature",
    type=str,
    default="成员函数",
    choices=[feat.name for feat in utils.LSF_list],
    help="The feature to translate the code for, e.g., '成员函数'.",
  )
  parser.add_argument(
    "--num",
    type=int,
    default=None,
    help="Number of C code files to translate, if not specified, all will be translated.",
  )
  args = parser.parse_args()
  for feat in utils.LSF_list:
    if feat.name == args.feature:
      feature = feat
      break
  else:
    raise ValueError(
      f"Feature '{args.feature}' not found in available features.")

  test_many(
    feature,
    args.num,
  )


if __name__ == "__main__":
  main()
