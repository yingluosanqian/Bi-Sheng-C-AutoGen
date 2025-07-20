/*
2_常量计算.md
constexpr函数计算斐波那契数列第n项，编译时递归
*/
#include <stdio.h>

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int result = fibonacci(10);
    printf("%d\n", result);
    return 0;
}