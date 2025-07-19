

from pathlib import Path
import subprocess
from utils import lang_sub_ft
import argparse


def parse_args():
  parser = argparse.ArgumentParser(
    description="Validate C and CBS program pairs.")
  parser.add_argument("--feature", type=str, required=True,
                      help="Feature to validate, e.g., '8_运算符重载'.")
  args = parser.parse_args()
  return args


def validate(
  c_code_fp: Path,
  bsc_code_fp: Path,
) -> bool:
  # 编译 c 文件
  try:
    timeout = 5
    c_exe = Path('binary_temp') / f"c_{c_code_fp.stem}"
    if not c_exe.parent.exists():
      c_exe.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(["clang", c_code_fp, "-o", c_exe],
                   check=True, timeout=timeout)
    c_out = subprocess.run([c_exe], capture_output=True,
                           text=True, check=True, timeout=timeout).stdout

    # 编译 cbs 文件（假设 cbs 文件可用 clang 编译）
    cbs_exe = Path('binary_temp') / f"cbs_{bsc_code_fp.stem}"
    if not cbs_exe.parent.exists():
      cbs_exe.parent.mkdir(parents=True, exist_ok=True)
    clang_args = [
      "-I/opt/compiler/llvm-project/libcbs/src/string",
      "-I/opt/compiler/llvm-project/libcbs/src/hash",
      "-I/opt/compiler/llvm-project/libcbs/src/raw_vec",
      "-I/opt/compiler/llvm-project/libcbs/src/cell",
      "-I/opt/compiler/llvm-project/libcbs/src/string",
      "-I/opt/compiler/llvm-project/libcbs/src/raw_table",
      "-I/opt/compiler/llvm-project/libcbs/src/vec",
      "-I/opt/compiler/llvm-project/libcbs/src/map",
      "-I/opt/compiler/llvm-project/libcbs/src/rc",
      "-I/opt/compiler/llvm-project/libcbs/src/result",
      "-I/opt/compiler/llvm-project/libcbs/src/list",
      "-I/opt/compiler/llvm-project/libcbs/src/option",
      "-I/opt/compiler/llvm-project/libcbs/src/bishengc_safety",
      "-I/opt/compiler/llvm-project/libcbs/src/scheduler",
      "/opt/compiler/llvm-project/libcbs/src/hash/sip.cbs",
      "/opt/compiler/llvm-project/libcbs/src/string/string.cbs",
      "/opt/compiler/llvm-project/libcbs/src/raw_table/raw_table.cbs",
      "/opt/compiler/llvm-project/libcbs/src/bishengc_safety/bishengc_safety.cbs",
      "/opt/compiler/llvm-project/libcbs/src/scheduler/scheduler.cbs",
    ]
    subprocess.run(["clang", bsc_code_fp, "-o", cbs_exe, *
                   clang_args], check=True, timeout=timeout)
    cbs_out = subprocess.run(
      [cbs_exe], capture_output=True, text=True, check=True, timeout=timeout).stdout

    if c_out == cbs_out:
      return True
    else:
      raise ValueError(
        f"Output mismatch for pair ({c_code_fp.name}, {bsc_code_fp.name}):\nC Output:\n{c_out}\nCBS Output:\n{cbs_out}")
  except Exception as e:
    print(f"Error processing pair ({c_code_fp.name}, {bsc_code_fp.name}): {e}")
    return False


def validate_many(
  dir: Path,
):
  c_files = list(dir.glob("c_*.c"))
  cbs_files = list(dir.glob("cbs_*.cbs"))

  # 建立 id 到文件的映射
  c_dict = {f.stem.split('_')[1]: f for f in c_files}
  cbs_dict = {f.stem.split('_')[1]: f for f in cbs_files}

  paired_ids = set(c_dict.keys()) & set(cbs_dict.keys())

  success_count = 0
  for id in paired_ids:
    c_file = c_dict[id]
    cbs_file = cbs_dict[id]
    print("Processing pair:", id)

    # 编译 c 文件
    if validate(c_file, cbs_file):
      print(f"Pair ({c_file.name}, {cbs_file.name}): Output matches.")
      dst_dir = Path("passed_programs") / \
          c_file.parent.relative_to("programs")
      dst_dir.mkdir(parents=True, exist_ok=True)
      dst_c = dst_dir / c_file.name
      dst_cbs = dst_dir / cbs_file.name
      dst_c.write_bytes(c_file.read_bytes())
      dst_cbs.write_bytes(cbs_file.read_bytes())
      success_count += 1
  print(f"Total pairs succeed: {success_count}")


def main():
  args = parse_args()

  validate_many(dir=Path('programs') / args.feature)


if __name__ == "__main__":
  main()
