/*
0_成员函数.md
为struct Array添加size成员函数，返回数组大小
*/
#include <stdio.h>
#include <stdlib.h>

struct Array {
    int *data;
    int length;
};

int array_size(struct Array *arr) {
    return arr->length;
}

int main() {
    struct Array arr;
    arr.data = malloc(5 * sizeof(int));
    arr.length = 5;
    
    for (int i = 0; i < arr.length; i++) {
        arr.data[i] = i + 1;
    }
    
    printf("%d\n", array_size(&arr));
    
    free(arr.data);
    return 0;
}