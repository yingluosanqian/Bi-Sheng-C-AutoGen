/*
4_无栈协程.md
async函数处理数组求和
*/
#include <stdio.h>
#include <stdlib.h>

int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int result = sum_array(arr, size);
    printf("%d", result);
    return 0;
}