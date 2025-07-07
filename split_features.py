
from pathlib import Path
from dpsk_llm import ask_llm
import re
import json


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


def get_sub_features_from_feature(feature_path: Path):
  with open(feature_path, 'r', encoding='utf-8') as f:
    feature_content = f.read()

  # Prepare prompts
  system_prompt = (
    "You are an expert technical writer for Bi-Sheng-C++ documentation. "
    "Bisheng C adopts a different strategy. It incorporates many enhanced designs based on the "
    "C language, such as stronger memory safety features and built-in support for concurrency. "
    "Moreover, these features can be incrementally adopted in existing codebases without requiring "
    "a full rewrite of legacy code. It can be said that Bisheng C is a superset of the C language."
    "Given a feature section from a Bi-Sheng-C++ manual, you will extract its sub-features. "
    "For each sub-feature, provide a JSON object with the following keys: "
    "'sub_feature' (the name), 'description' (a concise explanation), and 'example' (a code example). "
    "Return a JSON list of such objects. Use English."
  )

  user_prompt = (
    "Given the following C++ feature documentation, extract its sub-features. "
    "For each sub-feature, provide:\n"
    "- sub_feature: the name of the sub-feature\n"
    "- description: a concise explanation\n"
    "- example: a code example\n"
    "Return a JSON list, each item is a dict with keys: sub_feature, description, example.\n"
    "Example:\n"
    "[\n"
    "  {\n"
    "    \"sub_feature\": \"Static member function\",\n"
    "    \"description\": \"Call this function by the class name, without 'this' argument\",\n"
    "    \"example\": \"void MathUtils::print_pi() {\\n  printf(\\\"PI: 3.14\\\\n\\\");\\n}\\n\\nint main() {\\n  MathUtils::print_pi();\\n}\\n\"\n"
    "  }\n"
    "]\n"
    "Note: The 'example' field in the above example is short for demonstration purposes. In practice, the example can be of any length as needed.\n"
    "Now, here is the feature documentation:\n"
    f"{feature_content}\n"
  )

  # Call LLM
  response = ask_llm(system_prompt=system_prompt, user_prompt=user_prompt)
  # print("Resp:", response)
  # Preprocess response to extract JSON if wrapped in code block
  json_pattern = r"```(?:json)?\s*(.*?)\s*```"
  match = re.search(json_pattern, response, re.DOTALL | re.IGNORECASE)
  if match:
    response = match.group(1).strip()

  try:
    sub_features = json.loads(response)
  except Exception as e:
    print(f"Failed to parse LLM response: {e}")
    return

  # Prepare output directory
  feature_name = feature_path.stem
  out_dir = Path('docs') / feature_name
  out_dir.mkdir(parents=True, exist_ok=True)
  # Delete all files in out_dir before writing new sub-features
  for file in out_dir.glob("*"):
    if file.is_file():
      file.unlink()

  for idx, sub in enumerate(sub_features):
    sub_file = out_dir / f"sub_feature_{idx + 1}.md"
    with open(sub_file, 'w', encoding='utf-8') as f:
      f.write(f"# {sub.get('sub_feature', '')}\n\n")
      f.write(f"**Description:** {sub.get('description', '')}\n\n")
      f.write(f"**Example:**\n\n")
      f.write(f"``` bsc\n{sub.get('example', '')}\n```\n")


def main():
  doc_path = Path('bisheng-c-manual.md')

  feature_paths = split_features_from_doc(doc_path)

  for feature_path in feature_paths:
    get_sub_features_from_feature(feature_path)


if __name__ == "__main__":
  main()
