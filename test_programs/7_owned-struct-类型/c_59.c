/*
7_owned-struct-类型.md
创建owned struct Circle3D实例并初始化center和radius
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
} Point3D;

typedef struct {
    Point3D center;
    double radius;
} Circle3D;

int main() {
    Circle3D circle = {
        .center = {.x = 1.0, .y = 2.0, .z = 3.0},
        .radius = 5.0
    };
    
    printf("Circle center: (%.1f, %.1f, %.1f)\n", 
           circle.center.x, circle.center.y, circle.center.z);
    printf("Circle radius: %.1f\n", circle.radius);
    
    return 0;
}