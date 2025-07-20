/*
4_无栈协程.md
async递归函数计算阶乘
*/
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

int main() {
    int result = factorial(5);
    printf("{\"result\":%d}", result);
    return 0;
}