/*
6_内存安全.md
借用基本示例：创建对局部变量的不可变借用
*/
#include <stdio.h>

int main() {
    int local = 42;
    const int *borrow = &local;
    printf("%d\n", *borrow);
    return 0;
}