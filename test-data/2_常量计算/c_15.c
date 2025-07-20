/*
2_常量计算.md
使用is_integral判断类型是否为整数类型
*/
#include <stdio.h>

#define is_integral_type(x) _Generic((x), \
    char: 1, \
    signed char: 1, \
    unsigned char: 1, \
    short: 1, \
    unsigned short: 1, \
    int: 1, \
    unsigned int: 1, \
    long: 1, \
    unsigned long: 1, \
    long long: 1, \
    unsigned long long: 1, \
    default: 0)

int main() {
    int test_int = 42;
    float test_float = 3.14f;
    
    printf("%d\n", is_integral_type(test_int));
    printf("%d\n", is_integral_type(test_float));
    
    return 0;
}