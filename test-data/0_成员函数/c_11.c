/*
0_成员函数.md
为float类型添加square成员函数，计算浮点数平方
*/
#include <stdio.h>

// In standard C, we need to define a regular function
float square_float(float num) {
    return num * num;
}

int main() {
    float value = 3.5;
    float result = square_float(value);
    
    printf("The square of %.1f is %.2f\n", value, result);
    
    return 0;
}
