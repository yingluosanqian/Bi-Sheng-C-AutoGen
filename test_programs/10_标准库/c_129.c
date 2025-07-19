/*
10_标准库.md
使用Cell进行标志位轮转操作
*/
#include <stdio.h>

int main(void) {
    int flag = 0;
    
    // Toggle flag
    flag = !flag;
    flag = !flag;
    
    printf("%d\n", flag);
    return 0;
}