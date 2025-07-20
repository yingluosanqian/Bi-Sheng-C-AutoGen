/*
2_常量计算.md
constexpr函数计算两个整数的最大值，编译时求值
*/
#include <stdio.h>

int max_value(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int result = max_value(10, 20);
    printf("%d\n", result);
    return 0;
}