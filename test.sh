#!/bin/bash

declare -a dirs=(
  "test-data/0_成员函数:成员函数"
  "test-data/1_泛型:泛型"
  "test-data/2_常量计算:常量计算"
  "test-data/3_trait:trait"
  "test-data/4_无栈协程:无栈协程"
  "test-data/6_内存安全:内存安全"
  "test-data/7_owned-struct-类型:owned-struct-类型"
  "test-data/8_运算符重载:运算符重载"
  "test-data/9_非空指针:非空指针"
  "test-data/10_标准库:标准库"
)

for item in "${dirs[@]}"; do
  dir="${item%%:*}"
  flag="${item##*:}"
  cmd="python translation.py -m batch -i "$dir" -f "$flag" -o "results/$flag""
  echo "Execute cmd: ${cmd}"
  ${cmd}
done
