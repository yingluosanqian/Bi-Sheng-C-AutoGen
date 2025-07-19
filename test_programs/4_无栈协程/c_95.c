/*
4_无栈协程.md
async函数处理排序算法模拟
*/
#include <stdio.h>
#include <stdlib.h>

int simulate_sort(int *arr, int size) {
    // Simulate async sorting with sequential processing
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return 1;
}

int main() {
    int arr[] = {5, 2, 8, 1, 3};
    int size = sizeof(arr)/sizeof(arr[0]);
    
    int result = simulate_sort(arr, size);
    
    printf("[%d, %d, %d, %d, %d]", arr[0], arr[1], arr[2], arr[3], arr[4]);
    return 0;
}