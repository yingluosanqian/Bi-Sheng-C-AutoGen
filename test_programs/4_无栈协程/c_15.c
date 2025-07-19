/*
4_无栈协程.md
async函数处理两个数相除
*/
#include <stdio.h>
#include <stdlib.h>

int divide(int a, int b) {
    if (b == 0) return 0;
    return a / b;
}

int main() {
    int result = divide(10, 2);
    printf("%d", result);
    return 0;
}