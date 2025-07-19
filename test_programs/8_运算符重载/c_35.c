/*
8_运算符重载.md
重载+运算符实现多项式相加
*/
#include <stdio.h>

typedef struct {
    double coeffs[3];
} Polynomial;

Polynomial poly_add(Polynomial p1, Polynomial p2) {
    Polynomial result;
    for (int i = 0; i < 3; i++) {
        result.coeffs[i] = p1.coeffs[i] + p2.coeffs[i];
    }
    return result;
}

int main() {
    Polynomial p1 = {{1.0, 2.0, 3.0}};
    Polynomial p2 = {{4.0, 5.0, 6.0}};
    Polynomial p3 = poly_add(p1, p2);
    
    printf("%g %g %g\n", p3.coeffs[0], p3.coeffs[1], p3.coeffs[2]);
    return 0;
}