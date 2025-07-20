/*
1_泛型.md
泛型函数实现数组元素计数，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

int count_int_elements(int *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        count++;
    }
    return count;
}

int count_float_elements(float *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        count++;
    }
    return count;
}

int count_char_elements(char *arr, int size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        count++;
    }
    return count;
}

int main() {
    int int_arr[] = {1, 2, 3, 4, 5};
    float float_arr[] = {1.1, 2.2, 3.3};
    char char_arr[] = {'a', 'b', 'c', 'd'};
    
    int int_count = count_int_elements(int_arr, 5);
    int float_count = count_float_elements(float_arr, 3);
    int char_count = count_char_elements(char_arr, 4);
    
    printf("Int array count: %d\n", int_count);
    printf("Float array count: %d\n", float_count);
    printf("Char array count: %d\n", char_count);
    
    return 0;
}