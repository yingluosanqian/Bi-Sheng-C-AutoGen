/*
8_运算符重载.md
重载[]运算符实现安全数组访问
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct SafeArray {
    int *data;
    size_t size;
};

int safe_array_get(struct SafeArray *arr, size_t index) {
    if (index >= arr->size) {
        fprintf(stderr, "Index %zu out of bounds (size: %zu)\n", index, arr->size);
        exit(EXIT_FAILURE);
    }
    return arr->data[index];
}

void safe_array_set(struct SafeArray *arr, size_t index, int value) {
    if (index >= arr->size) {
        fprintf(stderr, "Index %zu out of bounds (size: %zu)\n", index, arr->size);
        exit(EXIT_FAILURE);
    }
    arr->data[index] = value;
}

int main() {
    struct SafeArray arr = {
        .data = (int[]){10, 20, 30, 40, 50},
        .size = 5
    };

    // Safe access in C requires explicit function calls
    printf("Element at index 2: %d\n", safe_array_get(&arr, 2));
    safe_array_set(&arr, 3, 45);
    printf("Element at index 3: %d\n", safe_array_get(&arr, 3));

    // This would safely exit with an error message
    // printf("Element at index 5: %d\n", safe_array_get(&arr, 5));

    return 0;
}
