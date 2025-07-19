/*
7_owned-struct-类型.md
定义owned struct Ray，包含origin和direction成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float origin;
    float direction;
} Ray;

void print_ray(Ray *ray) {
    printf("Ray: origin=%.2f, direction=%.2f\n", ray->origin, ray->direction);
}

int main() {
    Ray ray = {.origin = 1.0f, .direction = 2.5f};
    print_ray(&ray);
    return 0;
}