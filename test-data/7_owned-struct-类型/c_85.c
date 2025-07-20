/*
7_owned-struct-类型.md
创建owned struct Light实例并初始化position和color
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float position[3];
    float color[3];
} Light;

void print_light(const Light *light) {
    printf("Position: (%.1f, %.1f, %.1f)\n", 
           light->position[0], light->position[1], light->position[2]);
    printf("Color: (%.1f, %.1f, %.1f)\n", 
           light->color[0], light->color[1], light->color[2]);
}

int main() {
    Light light = {
        .position = {1.0f, 2.0f, 3.0f},
        .color = {1.0f, 0.5f, 0.0f}
    };
    
    print_light(&light);
    return 0;
}