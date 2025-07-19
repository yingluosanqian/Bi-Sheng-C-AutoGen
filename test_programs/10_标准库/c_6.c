/*
10_标准库.md
使用Vec的get方法获取动态数组的第一个元素
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* arr = malloc(3 * sizeof(int));
    arr[0] = 42;
    printf("%d\n", arr[0]);
    free(arr);
    return 0;
}