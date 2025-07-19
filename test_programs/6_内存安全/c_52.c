/*
6_内存安全.md
安全区回调示例：安全函数指针使用
*/
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int (*func_ptr)(int, int) = add;
    int result = func_ptr(3, 4);
    printf("%d\n", result);
    return 0;
}