/*
0_成员函数.md
为int类型添加factorial成员函数，计算阶乘
*/
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main() {
    int num = 5;
    int result = factorial(num);
    printf("%d! = %d\n", num, result);
    return 0;
}