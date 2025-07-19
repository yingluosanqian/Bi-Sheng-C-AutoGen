/*
2_常量计算.md
constexpr if在泛型函数中根据类型选择不同实现
*/
#include <stdio.h>

void process_int(int value) {
    printf("Processing integer: %d\n", value);
}

void process_float(float value) {
    printf("Processing float: %.2f\n", value);
}

int main() {
    int int_val = 42;
    float float_val = 3.14f;
    
    process_int(int_val);
    process_float(float_val);
    
    return 0;
}