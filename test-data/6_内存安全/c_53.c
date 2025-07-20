/*
6_内存安全.md
安全区递归示例：递归函数中的内存安全
*/
#include <stdio.h>
#include <stdlib.h>

int factorial(int n) {
    if (n <= 1) return 1;
    int *result = malloc(sizeof(int));
    *result = n * factorial(n - 1);
    int val = *result;
    free(result);
    return val;
}

int main() {
    printf("%d\n", factorial(5));
    return 0;
}