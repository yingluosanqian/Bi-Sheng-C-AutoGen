/*
4_无栈协程.md
async函数处理两个数相减
*/
#include <stdio.h>
#include <stdlib.h>

int subtract(int a, int b) {
    return a - b;
}

int main() {
    int result = subtract(10, 3);
    printf("{\"result\": %d}", result);
    return 0;
}