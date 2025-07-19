/*
7_owned-struct-类型.md
定义owned struct Transform，包含position、rotation和scale
*/
#include <stdio.h>
#include <stdlib.h>

struct Transform {
    float position[3];
    float rotation[4];
    float scale[3];
};

void print_transform(const struct Transform* t) {
    printf("Position: (%.2f, %.2f, %.2f)\n", t->position[0], t->position[1], t->position[2]);
    printf("Rotation: (%.2f, %.2f, %.2f, %.2f)\n", t->rotation[0], t->rotation[1], t->rotation[2], t->rotation[3]);
    printf("Scale: (%.2f, %.2f, %.2f)\n", t->scale[0], t->scale[1], t->scale[2]);
}

int main() {
    struct Transform t = {
        .position = {1.0f, 2.0f, 3.0f},
        .rotation = {0.0f, 0.0f, 0.0f, 1.0f},
        .scale = {1.0f, 1.0f, 1.0f}
    };
    
    print_transform(&t);
    return 0;
}