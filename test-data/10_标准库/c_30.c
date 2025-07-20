/*
10_标准库.md
使用RefCell在运行时借用检查下修改数据
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* p = malloc(sizeof(int));
    *p = 42;
    int* q = p;
    *q = 100;
    printf("%d\n", *p);
    free(p);
    return 0;
}