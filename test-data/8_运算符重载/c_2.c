/*
8_运算符重载.md
重载*运算符实现矩阵与标量的乘法
*/
#include <stdio.h>

typedef struct {
    int data[2][2];
} Matrix;

void matrix_multiply_scalar(Matrix *m, int scalar) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            m->data[i][j] *= scalar;
        }
    }
}

int main() {
    Matrix mat = {{{1, 2}, {3, 4}}};
    int scalar = 2;
    
    matrix_multiply_scalar(&mat, scalar);
    
    printf("%d %d\n%d %d", 
           mat.data[0][0], mat.data[0][1],
           mat.data[1][0], mat.data[1][1]);
    return 0;
}