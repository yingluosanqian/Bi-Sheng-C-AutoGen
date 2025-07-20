/*
7_owned-struct-类型.md
定义owned struct Point3D，包含x、y和z坐标
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
    float z;
} Point3D;

void print_point(Point3D *p) {
    printf("Point coordinates: (%.2f, %.2f, %.2f)\n", p->x, p->y, p->z);
}

int main() {
    Point3D p = {1.5f, 2.5f, 3.5f};
    print_point(&p);
    return 0;
}