/*
4_无栈协程.md
async函数实现简单的恢复功能
*/
#include <stdio.h>
#include <stdlib.h>

int TimeOut(int t) {
    return t;
}

int getData() {
    int t = TimeOut(42);
    return t;
}

int main() {
    int result = getData();
    printf("%d\n", result);
    return 0;
}