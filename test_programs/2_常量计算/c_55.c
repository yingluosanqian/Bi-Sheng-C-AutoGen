/*
2_常量计算.md
constexpr if结合sizeof进行内存布局优化
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[4];
    int count;
} SmallContainer;

typedef struct {
    void* data;
    int capacity;
    int count;
} LargeContainer;

void process_int() {
    SmallContainer container = {{1, 2, 3, 4}, 4};
    printf("Processing int: ");
    for (int i = 0; i < container.count; i++) {
        printf("%d ", container.data[i]);
    }
    printf("\n");
}

void process_double() {
    LargeContainer container;
    container.capacity = 4;
    container.count = 4;
    container.data = malloc(container.capacity * sizeof(double));
    
    double* arr = (double*)container.data;
    arr[0] = 1.0; arr[1] = 2.0; arr[2] = 3.0; arr[3] = 4.0;
    
    printf("Processing double: ");
    for (int i = 0; i < container.count; i++) {
        printf("%.1f ", arr[i]);
    }
    printf("\n");
    
    free(container.data);
}

int main() {
    process_int();
    process_double();
    return 0;
}