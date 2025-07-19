/*
1_泛型.md
泛型类型别名定义向量类型，简化数学向量声明
*/
#include <stdio.h>
#include <stdlib.h>

struct Vector2D {
    float data[2];
};

struct Vector3D {
    float data[3];
};

void print_vector2d(struct Vector2D *v) {
    printf("Vector2D: [%.1f, %.1f]\n", v->data[0], v->data[1]);
}

void print_vector3d(struct Vector3D *v) {
    printf("Vector3D: [%.1f, %.1f, %.1f]\n", v->data[0], v->data[1], v->data[2]);
}

int main() {
    struct Vector2D v2 = {{1.0, 2.0}};
    struct Vector3D v3 = {{1.0, 2.0, 3.0}};
    
    print_vector2d(&v2);
    print_vector3d(&v3);
    
    return 0;
}