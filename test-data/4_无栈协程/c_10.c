/*
4_无栈协程.md
async函数处理数组最小值
*/
#include <stdio.h>
#include <stdlib.h>

int find_min(int *arr, int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int arr[] = {5, 2, 9, 1, 7};
    int size = sizeof(arr)/sizeof(arr[0]);
    int min = find_min(arr, size);
    printf("%d\n", min);
    return 0;
}