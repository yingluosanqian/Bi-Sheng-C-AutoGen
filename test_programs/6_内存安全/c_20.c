/*
6_内存安全.md
安全区基本示例：在safe块中执行内存安全操作
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        return 1;
    }
    *ptr = 42;
    printf("%d\n", *ptr);
    free(ptr);
    return 0;
}