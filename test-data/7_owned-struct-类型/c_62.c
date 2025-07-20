/*
7_owned-struct-类型.md
定义owned struct Sphere，包含center和radius
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double center[3];
    double radius;
} Sphere;

void print_sphere(const Sphere *s) {
    printf("{\"center\":[%f,%f,%f],\"radius\":%f}", 
           s->center[0], s->center[1], s->center[2], s->radius);
}

int main() {
    Sphere s = {
        .center = {1.0, 2.0, 3.0},
        .radius = 5.0
    };
    print_sphere(&s);
    return 0;
}