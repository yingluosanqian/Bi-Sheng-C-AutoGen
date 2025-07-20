

from pathlib import Path
import subprocess
import tempfile
import logging
import os
import utils
logger = logging.getLogger(__name__)


def validate(
  c_code_fp: Path,
  bsc_code_fp: Path,
  timeout: int = 5,
) -> bool:
  try:
    with tempfile.TemporaryDirectory() as tmpdir:
      c_exe = Path(tmpdir) / f"c_{c_code_fp.stem}"
      clang_resp = subprocess.run(["clang", c_code_fp, "-o", c_exe], capture_output=True,
                                  check=True, timeout=timeout)
      if clang_resp.returncode != 0:
        logger.warning(
          f"Clang compilation failed for {c_code_fp.name}: {clang_resp.stderr.decode()}")
        return False
      c_out = subprocess.run([c_exe], capture_output=True,
                             text=True, check=True, timeout=timeout).stdout

      cbs_exe = Path(tmpdir) / f"cbs_{bsc_code_fp.stem}"
      clang_resp = subprocess.run(["clang", bsc_code_fp, "-o", cbs_exe, *
                      utils.ClangArgs], capture_output=True, check=True, timeout=timeout)
      if clang_resp.returncode != 0:
        logger.warning(
          f"Clang compilation failed for {c_code_fp.name}: {clang_resp.stderr.decode()}")
        return False
      cbs_out = subprocess.run(
        [cbs_exe], capture_output=True, text=True, check=True, timeout=timeout).stdout

      if c_out == cbs_out:
        return True
      else:
        raise ValueError(
          f"Output mismatch for pair ({c_code_fp.name}, {bsc_code_fp.name}):\nC Output:\n{c_out}\nCBS Output:\n{cbs_out}")
  except Exception as e:
    logger.warning(
      f"Error processing pair ({c_code_fp.name}, {bsc_code_fp.name}): {e}")
    return False
