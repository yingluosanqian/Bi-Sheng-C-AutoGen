/*
6_内存安全.md
借用解引用示例：安全解引用借用指针
*/
#include <stdio.h>
#include <stdlib.h>

void modify_value(int* ptr) {
    *ptr = 42;
}

int main() {
    int value = 0;
    int* ptr = &value;
    modify_value(ptr);
    printf("%d\n", value);
    return 0;
}