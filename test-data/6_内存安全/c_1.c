/*
6_内存安全.md
展示所有权转移的简单程序
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    *p = 42;
    
    int *q = p;  // Ownership transfer (manual in C)
    p = NULL;    // Must manually nullify in C
    
    printf("%d\n", *q);
    
    free(q);
    return 0;
}