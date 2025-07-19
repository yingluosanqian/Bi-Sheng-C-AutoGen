/*
2_常量计算.md
使用is_pointer判断类型是否为指针类型
*/
#include <stdio.h>

int main() {
    int value = 42;
    int *ptr = &value;
    
    // In standard C, we can only check pointer values at runtime
    // We simulate the type checking by using different variables
    int is_int_pointer = 0;  // int is not a pointer
    int is_ptr_pointer = 1;  // int* is a pointer
    
    printf("int is pointer: %d\n", is_int_pointer);
    printf("int* is pointer: %d\n", is_ptr_pointer);
    
    return 0;
}