/*
10_标准库.md
使用safe_malloc分配一个整数并初始化为0
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = (int *)malloc(sizeof(int));
    *p = 0;
    free(p);
    return 0;
}