#!/bin/bash

cd "$(dirname "$0")/compiled_success" || exit 1

OUTFILE="run_batch_result.txt"
> "$OUTFILE"

success_compile=0
fail_compile=0
success_run=0
fail_run=0

compile_fail_ids=()
run_fail_ids=()

echo "=== Compiling and Running BiSheng-C Programs from cbs_0 to cbs_60 ===" | tee -a "$OUTFILE"

for i in {0..150}; do
  SRC="cbs_${i}.cbs"
  OUT="cbs_${i}.out"

  echo "=== Compiling $SRC ===" | tee -a "$OUTFILE"

  if [ ! -f "$SRC" ]; then
    echo "❌ File not found: $SRC" | tee -a "$OUTFILE"
    fail_compile=$((fail_compile + 1))
    compile_fail_ids+=($i)
    echo "" >> "$OUTFILE"
    continue
  fi

  COMPILE_LOG=$(mktemp)
  /home/zya219/llvm-project/build/bin/clang \
    "$SRC" \
    -I/home/zya219/llvm-project/build/lib/clang/15.0.4/include \
    -L/home/zya219/llvm-project/build/lib \
    -lstdcbs \
    -o "$OUT" >"$COMPILE_LOG" 2>&1
  STATUS=$?

  cat "$COMPILE_LOG" | tee -a "$OUTFILE"
  rm "$COMPILE_LOG"

  if [ $STATUS -eq 0 ]; then
    echo "✅ Compilation succeeded: $SRC" | tee -a "$OUTFILE"
    success_compile=$((success_compile + 1))

    chmod +x "$OUT"
    echo "--- Running $OUT ---" | tee -a "$OUTFILE"

    RUN_LOG=$(mktemp)
    ./"$OUT" >"$RUN_LOG" 2>&1
    RUN_STATUS=$?

    cat "$RUN_LOG" | tee -a "$OUTFILE"
    rm "$RUN_LOG"

    if [ $RUN_STATUS -eq 0 ]; then
      echo "✅ Program exited normally." | tee -a "$OUTFILE"
      success_run=$((success_run + 1))
    else
      echo "❌ Runtime error (exit code $RUN_STATUS)" | tee -a "$OUTFILE"
      fail_run=$((fail_run + 1))
      run_fail_ids+=($i)
    fi

  else
    echo "❌ Compilation failed: $SRC" | tee -a "$OUTFILE"
    fail_compile=$((fail_compile + 1))
    compile_fail_ids+=($i)
  fi

  echo "" >> "$OUTFILE"
done

# 汇总
{
  echo "========== Summary =========="
  echo "✅ Compiled OK : $success_compile"
  echo "❌ Compile Fail: $fail_compile"
  echo "✅ Run OK      : $success_run"
  echo "❌ Run Fail    : $fail_run"
  echo -n "❌ Compile Fail IDs: "; echo "${compile_fail_ids[@]}"
  echo -n "❌ Run Fail IDs    : "; echo "${run_fail_ids[@]}"
} | tee -a "$OUTFILE"
