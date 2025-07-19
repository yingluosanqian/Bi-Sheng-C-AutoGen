/*
10_标准库.md
使用Rc的deref方法访问共享的整数
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* p = (int*)malloc(sizeof(int));
    *p = 42;
    
    // Manual reference counting simulation
    int* q = p;
    
    printf("%d\n", *p);
    
    free(p);
    // Must ensure q isn't used after free
    
    return 0;
}