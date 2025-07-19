/*
7_owned-struct-类型.md
创建owned struct Matrix4x4实例并初始化矩阵
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float data[4][4];
} Matrix4x4;

void print_matrix(Matrix4x4 *m) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Matrix4x4 mat = {
        .data = {
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f}
        }
    };
    
    print_matrix(&mat);
    return 0;
}