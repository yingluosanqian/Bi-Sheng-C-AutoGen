/*
6_内存安全.md
安全区内实现两个owned指针的所有权交换
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));
    
    *a = 10;
    *b = 20;
    
    // Swap ownership
    int *temp = a;
    a = b;
    b = temp;
    
    printf("a: %d, b: %d\n", *a, *b);
    
    free(a);
    free(b);
    return 0;
}