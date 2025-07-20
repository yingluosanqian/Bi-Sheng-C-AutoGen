/*
4_无栈协程.md
异步函数返回await表达式结果，展示合法return用法
*/
#include <stdio.h>

int read(int n) {
    return n * 2;
}

int main() {
    int result = read(5);
    printf("%d\n", result);
    return 0;
}