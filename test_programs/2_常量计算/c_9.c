/*
2_常量计算.md
constexpr函数计算两个整数的较小值
*/
#include <stdio.h>

/* In standard C, we can only create a runtime function */
int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    /* This calculation happens at runtime */
    int result = min(5, 10);
    
    /* We can't use this in static asserts or array sizes */
    printf("The minimum is: %d\n", result);
    
    return 0;
}
