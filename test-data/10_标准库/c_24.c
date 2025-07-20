/*
10_标准库.md
使用Rc共享一个整数所有权
*/
#include <stdlib.h>
#include <stdio.h>

int main() {
    int* p = (int*)malloc(sizeof(int));
    *p = 42;
    
    int* q = p; // Shared ownership (manual tracking required)
    
    printf("Value: %d\n", *q);
    
    free(p); // Must ensure no further use of q
    return 0;
}