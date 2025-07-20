/*
1_泛型.md
泛型函数实现数组元素映射转换
*/
#include <stdio.h>

void map_int(int *array, size_t size, int (*func)(int)) {
    for (size_t i = 0; i < size; i++) {
        array[i] = func(array[i]);
    }
}

int square_int(int x) {
    return x * x;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    map_int(arr, size, square_int);
    
    printf("Mapped array: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}
