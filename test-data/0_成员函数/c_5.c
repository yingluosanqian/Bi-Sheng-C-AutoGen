/*
0_成员函数.md
为float类型添加abs成员函数，返回浮点数绝对值
*/
#include <stdio.h>
#include <math.h>

int main() {
    float value1 = -3.14f;
    float value2 = 2.71f;
    float value3 = -0.0f;
    
    float abs1 = fabsf(value1);
    float abs2 = fabsf(value2);
    float abs3 = fabsf(value3);
    
    printf("Absolute value of %.2f is %.2f\n", value1, abs1);
    printf("Absolute value of %.2f is %.2f\n", value2, abs2);
    printf("Absolute value of %.2f is %.2f\n", value3, abs3);
    
    return 0;
}