/*
1_泛型.md
泛型函数实现数组元素求平均值，支持任意数值类型
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we need separate functions for each data type
int average_int(int arr[], int size) {
    if (size <= 0) return 0;
    
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return sum / size;
}

float average_float(float arr[], int size) {
    if (size <= 0) return 0.0f;
    
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return sum / size;
}

double average_double(double arr[], int size) {
    if (size <= 0) return 0.0;
    
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    
    return sum / size;
}

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    float float_arr[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    double double_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    
    int int_avg = average_int(int_arr, 5);
    float float_avg = average_float(float_arr, 5);
    double double_avg = average_double(double_arr, 5);
    
    printf("Integer array average: %d\n", int_avg);
    printf("Float array average: %.2f\n", float_avg);
    printf("Double array average: %.2f\n", double_avg);
    
    return 0;
}
