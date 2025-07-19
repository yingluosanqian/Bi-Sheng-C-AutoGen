/*
8_运算符重载.md
重载-运算符实现复数减法
*/
#include <stdio.h>

typedef struct {
    double real;
    double imag;
} Complex;

Complex complex_subtract(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

int main() {
    Complex c1 = {5.0, 3.0};
    Complex c2 = {2.0, 1.0};
    Complex c3 = complex_subtract(c1, c2);
    printf("%.1f %.1f\n", c3.real, c3.imag);
    return 0;
}