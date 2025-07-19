/*
7_owned-struct-类型.md
定义owned struct Camera，包含position和direction成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Camera {
    float position[3];
    float direction[3];
};

void print_camera(struct Camera *cam) {
    printf("Position: (%.2f, %.2f, %.2f)\n", 
           cam->position[0], cam->position[1], cam->position[2]);
    printf("Direction: (%.2f, %.2f, %.2f)\n", 
           cam->direction[0], cam->direction[1], cam->direction[2]);
}

int main() {
    struct Camera *cam = malloc(sizeof(struct Camera));
    if (!cam) return 1;
    
    cam->position[0] = 1.0f;
    cam->position[1] = 2.0f;
    cam->position[2] = 3.0f;
    
    cam->direction[0] = 0.0f;
    cam->direction[1] = 0.0f;
    cam->direction[2] = 1.0f;
    
    print_camera(cam);
    
    free(cam);
    return 0;
}