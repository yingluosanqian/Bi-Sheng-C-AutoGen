/*
8_运算符重载.md
重载-运算符实现3D向量相减
*/
#include <stdio.h>

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    Vec3 r;
    r.x = a.x - b.x;
    r.y = a.y - b.y;
    r.z = a.z - b.z;
    return r;
}

int main() {
    Vec3 v1 = {5, 7, 9};
    Vec3 v2 = {1, 2, 3};
    Vec3 result = vec3_sub(v1, v2);
    printf("Result: (%d, %d, %d)\n", result.x, result.y, result.z);
    return 0;
}