/*
1_泛型.md
泛型函数实现绝对值计算，适用于各种数值类型
*/
#include <stdio.h>
#include <stdlib.h>

int abs_int(int x) {
    return x < 0 ? -x : x;
}

float abs_float(float x) {
    return x < 0.0f ? -x : x;
}

double abs_double(double x) {
    return x < 0.0 ? -x : x;
}

int main() {
    int a = -42;
    float b = -3.14f;
    double c = -2.718;
    
    int result1 = abs_int(a);
    float result2 = abs_float(b);
    double result3 = abs_double(c);
    
    printf("%d\n", result1);
    printf("%.2f\n", result2);
    printf("%.3f\n", result3);
    
    return 0;
}