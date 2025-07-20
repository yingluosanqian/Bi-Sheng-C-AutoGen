/*
2_常量计算.md
constexpr函数计算整数的绝对值，使用条件表达式
*/
#include <stdio.h>

int abs_value(int x) {
    return (x < 0) ? -x : x;
}

int main() {
    int result = abs_value(-42);
    printf("%d\n", result);
    return 0;
}