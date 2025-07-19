/*
8_运算符重载.md
重载*运算符实现矩阵向量乘法
*/
#include <stdio.h>

typedef struct {
    float data[2];
} Vector;

typedef struct {
    float data[2][2];
} Matrix;

Vector multiply_matrix_vector(Matrix m, Vector v) {
    Vector result;
    result.data[0] = m.data[0][0] * v.data[0] + m.data[0][1] * v.data[1];
    result.data[1] = m.data[1][0] * v.data[0] + m.data[1][1] * v.data[1];
    return result;
}

int main() {
    Matrix m = {{{1.0, 2.0}, {3.0, 4.0}}};
    Vector v = {{5.0, 6.0}};
    Vector result = multiply_matrix_vector(m, v);
    printf("Result: [%.1f, %.1f]\n", result.data[0], result.data[1]);
    return 0;
}