/*
7_owned-struct-类型.md
定义owned struct Material，包含color和texture成员
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Material {
    char color[20];
    char texture[20];
};

void print_material(struct Material *mat) {
    printf("Color: %s, Texture: %s\n", mat->color, mat->texture);
}

int main() {
    struct Material mat = {
        .color = "red",
        .texture = "rough"
    };
    
    print_material(&mat);
    
    return 0;
}