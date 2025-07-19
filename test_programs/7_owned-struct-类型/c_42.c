/*
7_owned-struct-类型.md
定义owned struct Complex，包含real和imaginary成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double real;
    double imaginary;
} Complex;

void print_complex(Complex *c) {
    printf("Complex number: %.2f + %.2fi\n", c->real, c->imaginary);
}

int main() {
    Complex c = {3.14, 2.71};
    print_complex(&c);
    return 0;
}