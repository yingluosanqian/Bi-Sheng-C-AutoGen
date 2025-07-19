/*
6_内存安全.md
安全区指针限制示例：在safe区限制裸指针操作
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