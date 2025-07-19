/*
6_内存安全.md
使用borrow指针修改局部变量的值
*/
#include <stdio.h>

void modify_value(int *ptr) {
    *ptr = 42;
}

int main() {
    int x = 10;
    modify_value(&x);
    printf("%d\n", x);
    return 0;
}