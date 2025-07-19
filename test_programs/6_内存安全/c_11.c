/*
6_内存安全.md
可变借用示例：创建对局部变量的可变借用
*/
#include <stdio.h>

void modify_value(int *ptr) {
    *ptr = 42;
}

int main() {
    int value = 10;
    int *ptr = &value;
    modify_value(ptr);
    printf("Value: %d\n", value);
    return 0;
}