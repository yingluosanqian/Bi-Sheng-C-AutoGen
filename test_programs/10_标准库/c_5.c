/*
10_标准库.md
使用Vec创建一个整数动态数组并添加元素
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* arr = malloc(10 * sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    printf("%d %d\n", arr[0], arr[1]);
    free(arr);
    return 0;
}