/*
6_内存安全.md
安全区函数示例：声明safe函数并调用
*/
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    int result = add(2, 3);
    printf("%d\n", result);
    return 0;
}