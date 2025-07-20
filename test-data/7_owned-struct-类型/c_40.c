/*
7_owned-struct-类型.md
定义owned struct Vector3D，包含x、y和z成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector3D;

void print_vector(Vector3D *v) {
    printf("Vector: (%.2f, %.2f, %.2f)\n", v->x, v->y, v->z);
}

int main() {
    Vector3D vec = {1.5f, 2.5f, 3.5f};
    print_vector(&vec);
    return 0;
}