/*
7_owned-struct-类型.md
创建owned struct Matrix3x3实例并初始化矩阵
*/
#include <stdio.h>
#include <stdlib.h>

struct Matrix3x3 {
    float data[3][3];
};

void print_matrix(struct Matrix3x3 *m) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Matrix3x3 mat = {
        .data = {
            {1.0f, 2.0f, 3.0f},
            {4.0f, 5.0f, 6.0f},
            {7.0f, 8.0f, 9.0f}
        }
    };
    
    print_matrix(&mat);
    return 0;
}