/*
10_标准库.md
使用Option处理可能失败的整数除法
*/
#include <stdio.h>

int safe_divide(int a, int b, int *result) {
    if (b == 0) return 0; // failure
    *result = a / b;
    return 1; // success
}

int main(void) {
    int result;
    if (safe_divide(10, 2, &result)) {
        printf("%d\n", result);
    } else {
        printf("Division failed\n");
    }
    return 0;
}