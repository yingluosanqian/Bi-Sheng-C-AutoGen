/*
1_泛型.md
泛型函数实现两个数的乘法运算，适用于各种数值类型
*/
#include <stdio.h>

// In standard C, we need separate functions for each type
int multiply_int(int a, int b) {
    return a * b;
}

float multiply_float(float a, float b) {
    return a * b;
}

double multiply_double(double a, double b) {
    return a * b;
}

int main() {
    int int_result = multiply_int(5, 3);
    float float_result = multiply_float(2.5f, 4.0f);
    double double_result = multiply_double(3.14, 2.0);
    
    printf("Integer multiplication: %d\n", int_result);
    printf("Float multiplication: %.2f\n", float_result);
    printf("Double multiplication: %.2f\n", double_result);
    
    return 0;
}