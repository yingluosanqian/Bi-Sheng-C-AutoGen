/*
10_标准库.md
使用Vec在遍历中累加所有元素
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    int sum = 0;
    for (size_t i = 0; i < 3; i++) {
        sum += arr[i];
    }
    
    printf("%d\n", sum);
    free(arr);
    return 0;
}