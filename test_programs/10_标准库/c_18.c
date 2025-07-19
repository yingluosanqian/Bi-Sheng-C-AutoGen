/*
10_标准库.md
使用Option的None表示无值情况
*/
#include <stdio.h>
#include <stdlib.h>

int* find_value(int* arr, size_t len, int target) {
    for (size_t i = 0; i < len; i++) {
        if (arr[i] == target) {
            return &arr[i];
        }
    }
    return NULL;  // Using NULL to represent absence of value
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int* result = find_value(arr, 5, 3);
    if (result != NULL) {
        printf("%d\n", *result);
    } else {
        printf("None\n");
    }
    return 0;
}