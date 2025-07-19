/*
6_内存安全.md
展示可变借用的基本用法
*/
#include <stdio.h>

void modify(int* ptr) {
    *ptr = 42;
}

int main() {
    int value = 10;
    int* ptr = &value;
    modify(ptr);
    printf("%d\n", value);
    return 0;
}