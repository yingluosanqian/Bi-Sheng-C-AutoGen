/*
2_常量计算.md
constexpr if结合常量表达式进行条件判断
*/
#include <stdio.h>

int factorial_int(int n) {
    return (n <= 1) ? 1 : n * factorial_int(n - 1);
}

void print_type_info_int() {
    printf("Processing integer type\n");
}

void print_type_info_float() {
    printf("Processing non-integer type\n");
}

int main() {
    int result = factorial_int(5);
    printf("Factorial of 5: %d\n", result);
    
    print_type_info_int();
    print_type_info_float();
    
    return 0;
}