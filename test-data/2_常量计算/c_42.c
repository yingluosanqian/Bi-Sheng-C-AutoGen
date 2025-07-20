/*
2_常量计算.md
constexpr函数进行编译时数组初始化计算
*/
#include <stdio.h>

/* In standard C, we cannot use functions for compile-time array size calculation */
/* We must use preprocessor macros or hardcoded constants */
#define FACTORIAL_5 120
#define ARRAY_SIZE FACTORIAL_5

int main() {
    /* Array size must be a compile-time constant in C */
    int arr[ARRAY_SIZE];
    
    /* Initialize array with index values */
    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = i;
    }
    
    /* Print some values to verify */
    printf("%d\n", arr[0]);
    printf("%d\n", arr[10]);
    printf("%d\n", arr[119]);
    
    return 0;
}