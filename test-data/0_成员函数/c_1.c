/*
0_成员函数.md
为float类型添加print成员函数，打印浮点数值
*/
#include <stdio.h>

// In standard C, we need to define a global function that takes a float parameter
void print_float(float *value) {
    printf("%f\n", *value);
}

int main() {
    float number = 3.14159;
    
    // In standard C, we call the function and pass the float as a parameter
    print_float(&number);
    
    return 0;
}
