/*
10_标准库.md
使用Vec的len方法获取动态数组长度
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 1; arr[1] = 2; arr[2] = 3;
    
    // Manual length tracking required in C
    size_t len = 3;
    printf("%zu", len);
    
    free(arr);
    return 0;
}