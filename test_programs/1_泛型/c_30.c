/*
1_泛型.md
泛型联合体实现数值类型转换，支持int和float互转
*/
#include <stdio.h>
#include <stdlib.h>

union IntFloatConverter {
    int i;
    float f;
};

float int_to_float(int value) {
    union IntFloatConverter converter;
    converter.i = value;
    return (float)converter.i;
}

int float_to_int(float value) {
    union IntFloatConverter converter;
    converter.f = value;
    return (int)converter.f;
}

int main() {
    int int_val = 42;
    float float_val = 3.14f;
    
    float converted_float = int_to_float(int_val);
    int converted_int = float_to_int(float_val);
    
    printf("Int %d to float: %.2f\n", int_val, converted_float);
    printf("Float %.2f to int: %d\n", float_val, converted_int);
    
    return 0;
}