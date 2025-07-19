/*
2_常量计算.md
constexpr函数计算阶乘，使用递归实现编译时计算
*/
#include <stdio.h>

int factorial(int n) {
    return (n == 1) ? 1 : n * factorial(n - 1);
}

int main() {
    printf("%d\n", factorial(5));
    return 0;
}