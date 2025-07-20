/*
1_泛型.md
泛型函数实现数组元素求和，支持任意数值类型
*/
#include <stdio.h>

// In standard C, we need to create separate functions for each data type
int sum_int_array(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

float sum_float_array(float arr[], int size) {
    float sum = 0.0f;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

double sum_double_array(double arr[], int size) {
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    float float_arr[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    double double_arr[] = {1.11, 2.22, 3.33, 4.44, 5.55};
    
    int int_sum = sum_int_array(int_arr, 5);
    float float_sum = sum_float_array(float_arr, 5);
    double double_sum = sum_double_array(double_arr, 5);
    
    printf("Int array sum: %d\n", int_sum);
    printf("Float array sum: %.2f\n", float_sum);
    printf("Double array sum: %.2f\n", double_sum);
    
    return 0;
}
