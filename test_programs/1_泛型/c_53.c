/*
1_泛型.md
泛型函数实现简单的插入排序，支持任意可比较类型
*/
#include <stdio.h>
#include <stdlib.h>

// C implementation requires separate functions for each data type
void insertion_sort_int(int arr[], int size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void insertion_sort_float(float arr[], int size) {
    int i, j;
    float key;
    for (i = 1; i < size; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Helper functions to print arrays
void print_int_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_float_array(float arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%.1f ", arr[i]);
    }
    printf("\n");
}

int main() {
    int int_arr[] = {5, 2, 4, 6, 1, 3};
    int int_size = sizeof(int_arr) / sizeof(int_arr[0]);
    
    float float_arr[] = {5.5, 2.2, 4.4, 6.6, 1.1, 3.3};
    int float_size = sizeof(float_arr) / sizeof(float_arr[0]);
    
    // Sort and print integer array
    insertion_sort_int(int_arr, int_size);
    print_int_array(int_arr, int_size);
    
    // Sort and print float array
    insertion_sort_float(float_arr, float_size);
    print_float_array(float_arr, float_size);
    
    return 0;
}