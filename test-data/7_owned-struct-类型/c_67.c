/*
7_owned-struct-类型.md
创建owned struct Matrix2x2实例并初始化矩阵
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double data[2][2];
} Matrix2x2;

void print_matrix(Matrix2x2 *m) {
    printf("[[%.2f, %.2f],\n [%.2f, %.2f]]\n", 
           m->data[0][0], m->data[0][1],
           m->data[1][0], m->data[1][1]);
}

int main() {
    Matrix2x2 mat = {
        .data = {
            {1.0, 2.0},
            {3.0, 4.0}
        }
    };
    
    print_matrix(&mat);
    return 0;
}