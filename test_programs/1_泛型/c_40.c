/*
1_泛型.md
泛型类型别名定义指针类型，简化指针声明
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we need to define each pointer type explicitly
typedef int* IntPtr;
typedef float* FloatPtr;
typedef char* CharPtr;

// Function to print integer value from pointer
void print_int_value(IntPtr ptr) {
    if (ptr != NULL) {
        printf("Integer value: %d\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

// Function to print float value from pointer
void print_float_value(FloatPtr ptr) {
    if (ptr != NULL) {
        printf("Float value: %.2f\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

// Function to print character value from pointer
void print_char_value(CharPtr ptr) {
    if (ptr != NULL) {
        printf("Character value: %c\n", *ptr);
    } else {
        printf("Null pointer\n");
    }
}

int main() {
    // Allocate memory for our values
    IntPtr int_ptr = (IntPtr)malloc(sizeof(int));
    FloatPtr float_ptr = (FloatPtr)malloc(sizeof(float));
    CharPtr char_ptr = (CharPtr)malloc(sizeof(char));
    
    // Initialize values
    *int_ptr = 42;
    *float_ptr = 3.14f;
    *char_ptr = 'A';
    
    // Print values
    print_int_value(int_ptr);
    print_float_value(float_ptr);
    print_char_value(char_ptr);
    
    // Free allocated memory
    free(int_ptr);
    free(float_ptr);
    free(char_ptr);
    
    return 0;
}