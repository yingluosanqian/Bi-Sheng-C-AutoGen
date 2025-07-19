/*
10_标准库.md
使用Vec的set方法修改动态数组的第二个元素
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* arr = (int*)malloc(3 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    arr[1] = 99;  // Directly modify second element
    
    free(arr);
    return 0;
}