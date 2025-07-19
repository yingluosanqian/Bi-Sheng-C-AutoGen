/*
2_常量计算.md
综合使用constexpr常量、函数和if语句的数学计算
*/
#include <stdio.h>

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    const int n = 5;
    int fact_result = factorial(n);
    int fib_result = fibonacci(n);
    
    printf("Factorial of %d: %d\n", n, fact_result);
    printf("Fibonacci of %d: %d\n", n, fib_result);
    
    return 0;
}