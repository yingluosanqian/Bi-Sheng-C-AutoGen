/*
6_内存安全.md
使用owned指针实现内存屏障
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));
    *p = 42;
    printf("%d\n", *p);
    free(p);
    return 0;
}