/*
6_内存安全.md
安全内存释放示例：使用safe_free释放内存
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    printf("%d\n", *ptr);
    free(ptr);
    return 0;
}