/*
1_泛型.md
泛型函数实现简单的冒泡排序，支持任意可比较类型
*/
#include <stdio.h>
#include <stdlib.h>

// Bubble sort for integers
void bubble_sort_int(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Bubble sort for floats
void bubble_sort_float(float arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                float temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    // Sort integers
    int int_arr[] = {64, 34, 25, 12, 22, 11, 90};
    int int_size = sizeof(int_arr) / sizeof(int_arr[0]);
    bubble_sort_int(int_arr, int_size);
    
    printf("Sorted integers: ");
    for (int i = 0; i < int_size; i++) {
        printf("%d ", int_arr[i]);
    }
    printf("\n");
    
    // Sort floats
    float float_arr[] = {64.5, 34.2, 25.7, 12.3, 22.8, 11.1, 90.9};
    int float_size = sizeof(float_arr) / sizeof(float_arr[0]);
    bubble_sort_float(float_arr, float_size);
    
    printf("Sorted floats: ");
    for (int i = 0; i < float_size; i++) {
        printf("%.1f ", float_arr[i]);
    }
    printf("\n");
    
    return 0;
}