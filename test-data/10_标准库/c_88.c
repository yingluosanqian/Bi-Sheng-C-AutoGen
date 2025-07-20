/*
10_标准库.md
使用Cell实现开关变量的状态切换
*/
#include <stdio.h>

int main(void) {
    int toggle = 0;
    
    printf("Initial state: %d\n", toggle);
    toggle = !toggle;
    printf("Toggled state: %d\n", toggle);
    
    return 0;
}