/*
1_泛型.md
泛型函数实现两个数的加法运算，适用于各种数值类型
*/
#include <stdio.h>

int add_int(int a, int b) {
    return a + b;
}

float add_float(float a, float b) {
    return a + b;
}

double add_double(double a, double b) {
    return a + b;
}

int main() {
    int result_int = add_int(10, 20);
    float result_float = add_float(3.5f, 2.8f);
    double result_double = add_double(15.75, 8.25);
    
    printf("Integer addition: %d\n", result_int);
    printf("Float addition: %.1f\n", result_float);
    printf("Double addition: %.2f\n", result_double);
    
    return 0;
}