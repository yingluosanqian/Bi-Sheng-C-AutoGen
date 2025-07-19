/*
2_常量计算.md
constexpr if实现编译时算法选择
*/
#include <stdio.h>

int factorial_recursive(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial_recursive(n - 1);
}

int factorial_iterative(int n) {
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

int calculate_factorial(int n) {
    // Runtime decision - both algorithms are compiled
    if (n <= 5) {
        return factorial_iterative(n);
    } else {
        return factorial_recursive(n);
    }
}

int main() {
    printf("%d\n", calculate_factorial(5));
    printf("%d\n", calculate_factorial(6));
    return 0;
}