/*
6_内存安全.md
所有权转移示例：将owned指针所有权转移给另一个变量
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* p = malloc(sizeof(int));
    *p = 42;
    
    int* q = p;  // Ownership transfer in C is implicit
    
    printf("%d\n", *q);
    
    free(q);
    return 0;
}