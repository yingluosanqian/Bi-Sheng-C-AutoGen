/*
8_运算符重载.md
重载%运算符实现循环索引
*/
#include <stdio.h>

typedef struct {
    int *data;
    int size;
} CyclicArray;

int main() {
    int values[] = {10, 20, 30};
    int size = 3;
    CyclicArray arr = {values, size};
    
    int index = 5;
    int cyclic_index = index % size;
    if (cyclic_index < 0) cyclic_index += size;
    int result = arr.data[cyclic_index];
    
    printf("%d\n", result);
    return 0;
}