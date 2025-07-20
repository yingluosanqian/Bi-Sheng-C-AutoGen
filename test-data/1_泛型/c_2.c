/*
1_泛型.md
泛型函数实现数组中最小值查找，支持任意可比较类型
*/
#include <stdio.h>

int find_min_int(int arr[], int size) {
    int min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

float find_min_float(float arr[], int size) {
    float min = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int main() {
    int int_arr[] = {5, 2, 8, 1, 9};
    float float_arr[] = {3.5, 1.2, 4.8, 0.9, 2.1};
    
    int min_int = find_min_int(int_arr, 5);
    float min_float = find_min_float(float_arr, 5);
    
    printf("Min int: %d\n", min_int);
    printf("Min float: %.1f\n", min_float);
    
    return 0;
}