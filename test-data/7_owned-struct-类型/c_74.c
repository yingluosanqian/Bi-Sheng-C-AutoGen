/*
7_owned-struct-类型.md
定义owned struct Plane，包含normal和distance成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Plane {
    float normal[3];
    float distance;
};

void print_plane(struct Plane *p) {
    printf("Normal: (%.2f, %.2f, %.2f)\nDistance: %.2f\n",
           p->normal[0], p->normal[1], p->normal[2],
           p->distance);
}

int main() {
    struct Plane p = {
        .normal = {0.0f, 1.0f, 0.0f},
        .distance = 10.0f
    };
    
    print_plane(&p);
    return 0;
}