/*
0_成员函数.md
为struct Complex添加add成员函数，复数加法
*/
#include <stdio.h>
#include <stdlib.h>

struct Complex {
    double real;
    double imag;
};

void complex_add(struct Complex* a, struct Complex* b, struct Complex* result) {
    result->real = a->real + b->real;
    result->imag = a->imag + b->imag;
}

int main() {
    struct Complex c1 = {3.0, 4.0};
    struct Complex c2 = {1.0, 2.0};
    struct Complex result;
    
    complex_add(&c1, &c2, &result);
    
    printf("Result: %.1f + %.1fi\n", result.real, result.imag);
    
    return 0;
}