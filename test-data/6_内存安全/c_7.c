/*
6_内存安全.md
安全区内禁止裸指针解引用的示例
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));
    *p = 42;  // Bare pointer dereference allowed in standard C
    printf("%d\n", *p);
    free(p);
    return 0;
}