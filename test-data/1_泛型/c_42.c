/*
1_泛型.md
泛型类型别名定义函数指针类型，简化函数指针声明
*/
#include <stdio.h>

/* Standard C requires separate typedef for each function pointer type */
typedef int (*IntBinaryOp)(int, int);
typedef float (*FloatBinaryOp)(float, float);
typedef double (*DoubleBinaryOp)(double, double);

int add_int(int a, int b) {
    return a + b;
}

int mul_int(int a, int b) {
    return a * b;
}

float add_float(float a, float b) {
    return a + b;
}

float mul_float(float a, float b) {
    return a * b;
}

double add_double(double a, double b) {
    return a + b;
}

double mul_double(double a, double b) {
    return a * b;
}

int main() {
    /* Using function pointers with verbose type declarations */
    IntBinaryOp int_ops[2] = {add_int, mul_int};
    FloatBinaryOp float_ops[2] = {add_float, mul_float};
    DoubleBinaryOp double_ops[2] = {add_double, mul_double};
    
    int int_result1 = int_ops[0](5, 3);
    int int_result2 = int_ops[1](5, 3);
    
    float float_result1 = float_ops[0](5.5f, 3.2f);
    float float_result2 = float_ops[1](5.5f, 3.2f);
    
    double double_result1 = double_ops[0](5.5, 3.2);
    double double_result2 = double_ops[1](5.5, 3.2);
    
    printf("Int: %d %d\n", int_result1, int_result2);
    printf("Float: %.1f %.1f\n", float_result1, float_result2);
    printf("Double: %.1f %.1f\n", double_result1, double_result2);
    
    return 0;
}