/*
4_无栈协程.md
async函数处理数组最大值
*/
#include <stdio.h>
#include <stdlib.h>

int find_max(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int arr[] = {3, 7, 2, 9, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max = find_max(arr, size);
    printf("%d\n", max);
    return 0;
}