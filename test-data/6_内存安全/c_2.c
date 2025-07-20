/*
6_内存安全.md
安全释放示例：在作用域结束前正确释放owned指针
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