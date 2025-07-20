/*
0_成员函数.md
为struct Complex添加multiply成员函数，复数乘法
*/
#include <stdio.h>

// Complex number structure
typedef struct Complex {
    double real;
    double imag;
} Complex;

// Function to multiply two complex numbers
Complex multiply_complex(Complex* c1, Complex c2) {
    Complex result;
    result.real = c1->real * c2.real - c1->imag * c2.imag;
    result.imag = c1->real * c2.imag + c1->imag * c2.real;
    return result;
}

// Function to print a complex number
void print_complex(Complex c) {
    if (c.imag >= 0) {
        printf("%.2f + %.2fi\n", c.real, c.imag);
    } else {
        printf("%.2f - %.2fi\n", c.real, -c.imag);
    }
}

int main() {
    Complex c1 = {3.0, 4.0};
    Complex c2 = {1.0, 2.0};
    
    printf("c1 = ");
    print_complex(c1);
    
    printf("c2 = ");
    print_complex(c2);
    
    Complex result = multiply_complex(&c1, c2);
    
    printf("c1 * c2 = ");
    print_complex(result);
    
    return 0;
}
