/*
0_成员函数.md
为struct Array添加set成员函数，设置指定索引元素
*/
#include <stdio.h>
#include <stdlib.h>

struct Array {
    int *data;
    int size;
};

void array_set(struct Array *arr, int index, int value) {
    if (index >= 0 && index < arr->size) {
        arr->data[index] = value;
    }
}

struct Array* array_init(int size) {
    struct Array *arr = malloc(sizeof(struct Array));
    arr->data = malloc(sizeof(int) * size);
    arr->size = size;
    for (int i = 0; i < size; i++) {
        arr->data[i] = 0;
    }
    return arr;
}

void array_print(struct Array *arr) {
    printf("Array: ");
    for (int i = 0; i < arr->size; i++) {
        printf("%d ", arr->data[i]);
    }
    printf("\n");
}

void array_free(struct Array *arr) {
    free(arr->data);
    free(arr);
}

int main() {
    struct Array *arr = array_init(5);
    
    array_set(arr, 0, 10);
    array_set(arr, 2, 20);
    array_set(arr, 4, 30);
    
    array_print(arr);
    
    array_free(arr);
    return 0;
}