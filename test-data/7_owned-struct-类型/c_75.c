/*
7_owned-struct-类型.md
创建owned struct Plane实例并初始化normal和distance
*/
#include <stdio.h>
#include <stdlib.h>

struct Plane {
    float normal[3];
    float distance;
};

int main() {
    struct Plane plane = {
        .normal = {0.0f, 1.0f, 0.0f},
        .distance = 10.0f
    };
    
    printf("Plane normal: (%.1f, %.1f, %.1f)\n", 
           plane.normal[0], plane.normal[1], plane.normal[2]);
    printf("Plane distance: %.1f\n", plane.distance);
    
    return 0;
}