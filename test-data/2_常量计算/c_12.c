/*
2_常量计算.md
constexpr函数计算整数的平方，简单编译时运算
*/
#include <stdio.h>

// In standard C, we can use macros for compile-time constants
#define SQUARE(x) ((x) * (x))

// Or use a regular function (evaluated at runtime)
int square(int x) {
    return x * x;
}

int main() {
    // Use the macro for a compile-time constant
    int arr[SQUARE(3)]; // Array of size 9
    
    // Use the function for runtime calculation
    int x = 4;
    int result = square(x);
    
    printf("Square of %d is %d\n", x, result);
    return 0;
}