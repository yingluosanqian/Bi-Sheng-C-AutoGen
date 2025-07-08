

from pathlib import Path
import subprocess


def validate(
  dir: Path,
  delete_failed_files: bool = True,
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

    # 编译 c 文件
    try:
      c_exe = Path('binary_temp') / f"c_{id}"
      if not c_exe.parent.exists():
        c_exe.parent.mkdir(parents=True, exist_ok=True)
      subprocess.run(["clang", c_file, "-o", c_exe], check=True)
      c_out = subprocess.run([c_exe], capture_output=True,
                            text=True, check=True).stdout

      # 编译 cbs 文件（假设 cbs 文件可用 clang 编译）
      cbs_exe = Path('binary_temp') / f"cbs_{id}"
      if not cbs_exe.parent.exists():
        cbs_exe.parent.mkdir(parents=True, exist_ok=True)
      subprocess.run(["clang", cbs_file, "-o", cbs_exe], check=True)
      cbs_out = subprocess.run(
        [cbs_exe], capture_output=True, text=True, check=True).stdout

      if c_out == cbs_out:
        print(f"Pair {id}: Output matches.")
        success_count += 1
      else:
        raise ValueError(
          f"Output mismatch for pair {id}:\nC Output:\n{c_out}\nCBS Output:\n{cbs_out}")
    except Exception as e:
      print(f"Error processing pair {id}.")
      if delete_failed_files:
        print(f"Deleting failed files: {c_file}, {cbs_file}")
        c_file.unlink(missing_ok=True)
        cbs_file.unlink(missing_ok=True)
  print(f"Total pairs succeed: {success_count}")


def main():
  # validate(
  #   dir=Path('programs/0_成员函数')
  # )
  validate(dir=Path('programs/1_泛型'))


if __name__ == "__main__":
  main()
