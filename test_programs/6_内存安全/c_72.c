/*
6_内存安全.md
安全区系统编程示例：系统级安全编程
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p = malloc(sizeof(int));
    *p = 42;
    
    int *q = p;
    printf("%d\n", *q);
    
    free(p);
    // Potential use-after-free if q is used after this point
    return 0;
}