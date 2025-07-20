/*
7_owned-struct-类型.md
创建owned struct Vector3D实例并初始化x、y和z
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

void print_vector(Vector3D *vec) {
    printf("Vector: (%.2f, %.2f, %.2f)\n", vec->x, vec->y, vec->z);
}

int main() {
    Vector3D vec = {1.5f, 2.5f, 3.5f};
    print_vector(&vec);
    return 0;
}