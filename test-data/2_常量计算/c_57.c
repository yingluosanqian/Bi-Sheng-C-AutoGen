/*
2_常量计算.md
constexpr函数实现编译时校验和计算
*/
#include <stdio.h>

int factorial(int n) {
    return (n == 1) ? 1 : n * factorial(n - 1);
}

int main() {
    int result = factorial(5);
    printf("%d\n", result);
    return 0;
}