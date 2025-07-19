/*
1_泛型.md
常量泛型实现固定大小数组结构体，大小可配置
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we need to either:
// 1. Use a fixed size array (not configurable)
// 2. Use dynamic allocation (has runtime overhead)

#define MAX_SIZE 100

// Option 1: Fixed size array (not easily configurable)
struct FixedArray {
    int data[MAX_SIZE];
    int size;
};

// Initialize fixed array
void initFixedArray(struct FixedArray* arr, int size) {
    if (size > MAX_SIZE) {
        printf("Error: Size exceeds maximum capacity\n");
        arr->size = 0;
        return;
    }
    arr->size = size;
    for (int i = 0; i < size; i++) {
        arr->data[i] = 0;
    }
}

// Get element at index
int getElement(struct FixedArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Error: Index out of bounds\n");
        return -1;
    }
    return arr->data[index];
}

// Set element at index
void setElement(struct FixedArray* arr, int index, int value) {
    if (index < 0 || index >= arr->size) {
        printf("Error: Index out of bounds\n");
        return;
    }
    arr->data[index] = value;
}

int main() {
    struct FixedArray arr;
    
    // Initialize with size 5
    initFixedArray(&arr, 5);
    
    // Set some values
    setElement(&arr, 0, 10);
    setElement(&arr, 1, 20);
    setElement(&arr, 2, 30);
    setElement(&arr, 3, 40);
    setElement(&arr, 4, 50);
    
    // Print the values
    printf("Array contents:\n");
    for (int i = 0; i < arr.size; i++) {
        printf("arr[%d] = %d\n", i, getElement(&arr, i));
    }
    
    return 0;
}
