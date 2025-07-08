
from pathlib import Path
from dpsk_llm import ask_llm
import re
import json
from tqdm import tqdm


def split_features_from_doc(doc_path: Path) -> list[Path]:
  '''
  Rule-based feature extraction from a document.
  '''
  with open(doc_path, 'r', encoding='utf-8') as file:
    content = file.read()
    # Find all top-level features between ## 成员函数 and ## 标准库
    pattern = r'(## .+?)(?=^## |\Z)'  # Match sections starting with ##
    matches = re.findall(pattern, content, flags=re.DOTALL | re.MULTILINE)

    start, end = None, None
    for i, section in enumerate(matches):
      if section.startswith('## 成员函数'):
        start = i
      if section.startswith('## 标准库'):
        end = i
        break

    features_path = []
    if start is not None and end is not None:
      features = matches[start:end + 1]
      for idx, feature in enumerate(features):
        # Extract the feature name after ##
        first_line = feature.splitlines()[0]
        feature_name = first_line.lstrip('#').strip().replace(' ', '-')
        out_path = Path('docs') / f'{idx}_{feature_name}.md'
        if not out_path.parent.exists():
          out_path.parent.mkdir(parents=True, exist_ok=True)
        with open(out_path, 'w', encoding='utf-8') as f:
          f.write(feature.strip() + '\n')
        features_path.append(out_path)
    return features_path


def gen_program_desc():
  def gen(
    input_filepath: Path,
    output_filepath: Path,
    num_of_program: int = 50,
  ):
    with input_filepath.open('r') as f:
      feature_content = f.read()

    return_format = "返回 json 格式的列表，列表的每个元素是一个字符串吗，例如：\n" \
        "[\n" \
        "  \"...\",\n" \
        "  \"...\",\n" \
        "  ...\n" \
        "]\n"

    system_prompt = "You are a helpful assistant that generates a program description based on the provided feature documentation."
    user_prompt = f"我要求你描述 {num_of_program} 个尽量简单的 C 语言程序，涉及到如下概念，能体现出如下特性：\n" + \
        feature_content + "\n返回格式参考：" + return_format
    response = ask_llm(system_prompt=system_prompt, user_prompt=user_prompt)

    json_pattern = r"```(?:json)?\s*(.*?)\s*```"
    match = re.search(json_pattern, response, re.DOTALL | re.IGNORECASE)
    if match:
      response = match.group(1).strip()

    with output_filepath.open('w', encoding='utf-8') as f:
      try:
        response = json.loads(response)
        json.dump(response, f, ensure_ascii=False, indent=2)
        print(f"Program description saved to {output_filepath}")
      except json.JSONDecodeError as e:
        print(f"Failed to parse JSON response: {e}")
        print("Response was:", response)

  md_files = list(Path('docs').glob('*.md'))
  for md_file in tqdm(md_files, desc="Generating program descriptions"):
    out_json = Path('program_desc') / (md_file.stem + '.json')
    out_json.parent.mkdir(parents=True, exist_ok=True)
    gen(
      input_filepath=md_file,
      output_filepath=out_json,
    )


def main():
  doc_path = Path('bisheng-c-manual.md')

  split_features_from_doc(doc_path)

  gen_program_desc()


if __name__ == "__main__":
  main()
