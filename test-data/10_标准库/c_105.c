/*
10_标准库.md
使用Vec的remove方法删除指定下标的元素
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(3 * sizeof(int));
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    // Manually remove element at index 1
    for (size_t i = 1; i < 2; i++) {
        arr[i] = arr[i + 1];
    }
    arr = realloc(arr, 2 * sizeof(int));

    printf("%d\n", arr[0]);
    printf("%d\n", arr[1]);
    
    free(arr);
    return 0;
}