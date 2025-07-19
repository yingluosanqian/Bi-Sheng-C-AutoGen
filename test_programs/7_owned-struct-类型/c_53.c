/*
7_owned-struct-类型.md
创建owned struct Point3D实例并初始化坐标
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

void print_point(Point3D *p) {
    printf("Point coordinates: (%.2f, %.2f, %.2f)\n", p->x, p->y, p->z);
}

int main() {
    Point3D point = {1.0, 2.0, 3.0};
    print_point(&point);
    return 0;
}