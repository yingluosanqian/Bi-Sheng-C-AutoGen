/*
10_标准库.md
使用Option的is_some方法检查是否有值
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *ptr = NULL;
    
    if (ptr != NULL) {
        printf("Has value\n");
    } else {
        printf("No value\n");
    }
    
    return 0;
}