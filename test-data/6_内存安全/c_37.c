/*
6_内存安全.md
安全内存分配示例：使用safe_malloc分配内存
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        return 1;
    }
    *p = 42;
    printf("%d\n", *p);
    free(p);
    return 0;
}