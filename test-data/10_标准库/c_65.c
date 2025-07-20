/*
10_标准库.md
使用Vec的clear方法清空数组所有元素
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    // Clearing array in C requires manual size tracking
    for (size_t i = 0; i < 3; i++) {
        arr[i] = 0; // Or free and reallocate
    }
    
    free(arr);
    return 0;
}