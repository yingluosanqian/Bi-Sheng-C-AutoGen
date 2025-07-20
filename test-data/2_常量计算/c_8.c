/*
2_常量计算.md
constexpr函数计算数组元素个数，使用sizeof表达式
*/
#include <stdio.h>

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main() {
    int original_array[] = {1, 2, 3, 4, 5};
    int size = ARRAY_SIZE(original_array);
    
    int new_array[5];  /* Must use literal size in C */
    
    for (int i = 0; i < size; i++) {
        new_array[i] = original_array[i] * 2;
    }
    
    printf("Array size: %d\n", size);
    printf("Elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", new_array[i]);
    }
    printf("\n");
    
    return 0;
}