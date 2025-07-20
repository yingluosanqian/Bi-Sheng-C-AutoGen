/*
2_常量计算.md
constexpr函数使用三元运算符进行条件选择
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