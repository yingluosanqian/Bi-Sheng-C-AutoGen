/*
2_常量计算.md
使用constexpr定义编译时字符常量，并在static_assert中验证
*/
#include <stdio.h>

// In standard C, we use #define or enum for compile-time constants
#define MAX_NAME_LENGTH 10

enum {
    MIN_NAME_LENGTH = 3
};

int main() {
    // We can use these constants for array sizes
    char name[MAX_NAME_LENGTH];
    
    // But we can't use static_assert with these constants in C89/C90
    // C11 added _Static_assert but it's not available in all C implementations
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    _Static_assert(MAX_NAME_LENGTH > MIN_NAME_LENGTH, "Maximum name length must be greater than minimum");
#endif
    
    printf("Maximum name length: %d\n", MAX_NAME_LENGTH);
    printf("Minimum name length: %d\n", MIN_NAME_LENGTH);
    
    return 0;
}