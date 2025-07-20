/*
2_常量计算.md
使用is_convertible判断类型转换的可能性
*/
#include <stdio.h>

// In standard C, we need to use macros and other techniques to simulate type traits
#define IS_INT_CONVERTIBLE_TO_FLOAT 1
#define IS_INT_CONVERTIBLE_TO_INT_PTR 0
#define IS_FLOAT_CONVERTIBLE_TO_INT 1

int main() {
    printf("Can int be converted to float? %s\n", IS_INT_CONVERTIBLE_TO_FLOAT ? "Yes" : "No");
    printf("Can int be converted to int*? %s\n", IS_INT_CONVERTIBLE_TO_INT_PTR ? "Yes" : "No");
    printf("Can float be converted to int? %s\n", IS_FLOAT_CONVERTIBLE_TO_INT ? "Yes" : "No");
    
    return 0;
}