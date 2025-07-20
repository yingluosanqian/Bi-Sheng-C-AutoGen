/*
10_标准库.md
使用safe_malloc分配一个浮点数并初始化为3.14
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    float *p = (float *)malloc(sizeof(float));
    *p = 3.14f;
    free(p);
    return 0;
}