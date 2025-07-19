/*
10_标准库.md
使用Vec的pop方法移除动态数组的最后一个元素
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    size_t len = 3;
    int last = arr[len-1];
    len--;
    
    printf("%d\n", last);
    free(arr);
    return 0;
}