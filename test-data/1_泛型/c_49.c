/*
1_泛型.md
泛型函数实现数组查找，支持任意类型元素查找
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Standard C requires separate functions for each data type
int find_int(int *array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int find_float(float *array, int size, float target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int find_char(char *array, int size, char target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    int int_array[] = {10, 20, 30, 40, 50};
    float float_array[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    char char_array[] = {'a', 'b', 'c', 'd', 'e'};
    
    int int_result = find_int(int_array, 5, 30);
    int float_result = find_float(float_array, 5, 3.3);
    int char_result = find_char(char_array, 5, 'c');
    
    printf("Integer found at index: %d\n", int_result);
    printf("Float found at index: %d\n", float_result);
    printf("Character found at index: %d\n", char_result);
    
    return 0;
}