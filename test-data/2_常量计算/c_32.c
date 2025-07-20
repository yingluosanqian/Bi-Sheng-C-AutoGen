/*
2_常量计算.md
使用constexpr if实现编译时递归终止条件
*/
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int result = factorial(5);
    printf("%d\n", result);
    return 0;
}