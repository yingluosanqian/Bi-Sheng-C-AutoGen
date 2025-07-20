/*
1_泛型.md
泛型函数实现数组中最大值查找，支持任意可比较类型
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we need separate functions for different types
int find_max_int(int arr[], int size) {
    int max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

float find_max_float(float arr[], int size) {
    float max = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int main() {
    int int_array[] = {5, 9, 3, 7, 2};
    float float_array[] = {5.5, 9.2, 3.7, 7.1, 2.8};
    
    int max_int = find_max_int(int_array, 5);
    float max_float = find_max_float(float_array, 5);
    
    printf("Max integer: %d\n", max_int);
    printf("Max float: %.1f\n", max_float);
    
    return 0;
}
