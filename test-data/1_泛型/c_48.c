/*
1_泛型.md
泛型函数实现数组反转，支持任意类型数组
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_int_array(int *arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void reverse_float_array(float *arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        float temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void reverse_char_array(char *arr, int size) {
    for (int i = 0; i < size / 2; i++) {
        char temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void print_int_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_float_array(float *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%.1f ", arr[i]);
    }
    printf("\n");
}

void print_char_array(char *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%c ", arr[i]);
    }
    printf("\n");
}

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    int int_size = sizeof(int_arr) / sizeof(int_arr[0]);
    
    float float_arr[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    int float_size = sizeof(float_arr) / sizeof(float_arr[0]);
    
    char char_arr[] = {'a', 'b', 'c', 'd', 'e'};
    int char_size = sizeof(char_arr) / sizeof(char_arr[0]);
    
    printf("Original arrays:\n");
    printf("Int array: ");
    print_int_array(int_arr, int_size);
    printf("Float array: ");
    print_float_array(float_arr, float_size);
    printf("Char array: ");
    print_char_array(char_arr, char_size);
    
    reverse_int_array(int_arr, int_size);
    reverse_float_array(float_arr, float_size);
    reverse_char_array(char_arr, char_size);
    
    printf("Reversed arrays:\n");
    printf("Int array: ");
    print_int_array(int_arr, int_size);
    printf("Float array: ");
    print_float_array(float_arr, float_size);
    printf("Char array: ");
    print_char_array(char_arr, char_size);
    
    return 0;
}