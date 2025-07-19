/*
7_owned-struct-类型.md
定义owned struct Matrix4x4，包含十六个float元素
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float elements[16];
} Matrix4x4;

void print_matrix(Matrix4x4 *m) {
    printf("[");
    for (int i = 0; i < 16; i++) {
        printf("%.2f", m->elements[i]);
        if (i < 15) printf(", ");
    }
    printf("]\n");
}

int main() {
    Matrix4x4 mat = {
        .elements = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        }
    };
    
    print_matrix(&mat);
    return 0;
}