/*
0_成员函数.md
为struct Array添加get成员函数，获取指定索引元素
*/
#include <stdio.h>
#include <stdlib.h>

struct Array {
    int *data;
    int size;
};

int get_array_element(struct Array *arr, int index) {
    if (index >= 0 && index < arr->size) {
        return arr->data[index];
    }
    return -1;
}

int main() {
    struct Array arr;
    arr.size = 5;
    arr.data = (int*)malloc(arr.size * sizeof(int));
    
    for (int i = 0; i < arr.size; i++) {
        arr.data[i] = i * 10;
    }
    
    int element = get_array_element(&arr, 2);
    printf("%d\n", element);
    
    free(arr.data);
    return 0;
}