/*
1_泛型.md
泛型函数实现两个数的交换，适用于int, float, double等类型
*/
#include <stdio.h>

// Standard C requires separate swap functions for each data type
void swap_int(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_float(float* a, float* b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void swap_double(double* a, double* b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 5, b = 10;
    swap_int(&a, &b);
    printf("Swapped integers: a = %d, b = %d\n", a, b);
    
    float c = 3.14, d = 2.71;
    swap_float(&c, &d);
    printf("Swapped floats: c = %.2f, d = %.2f\n", c, d);
    
    double e = 9.99, f = 8.88;
    swap_double(&e, &f);
    printf("Swapped doubles: e = %.2f, f = %.2f\n", e, f);
    
    return 0;
}