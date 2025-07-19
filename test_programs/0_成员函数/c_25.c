/*
0_成员函数.md
为float类型添加sign成员函数，获取数值符号
*/
#include <stdio.h>
#include <stdbool.h>

// Standard C approach - global function
bool float_sign(const float* num) {
    return *num >= 0;
}

int main() {
    float a = 3.14f;
    float b = -2.718f;
    
    printf("Sign of a (3.14): %s\n", float_sign(&a) ? "positive" : "negative");
    printf("Sign of b (-2.718): %s\n", float_sign(&b) ? "positive" : "negative");
    
    return 0;
}
