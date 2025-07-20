/*
10_标准库.md
使用Cell修改一个被共享的整数
*/
#include <stdio.h>

int main() {
    int shared = 0;
    int *p1 = &shared;
    int *p2 = &shared;
    
    *p1 = 42;
    printf("%d\n", *p2);
    
    return 0;
}