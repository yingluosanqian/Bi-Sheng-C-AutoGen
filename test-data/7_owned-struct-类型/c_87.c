/*
7_owned-struct-类型.md
创建owned struct Material实例并初始化color和texture
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char color[20];
    char texture[20];
} Material;

void print_material(const Material *mat) {
    printf("{\"color\": \"%s\", \"texture\": \"%s\"}", mat->color, mat->texture);
}

int main() {
    Material mat;
    strcpy(mat.color, "red");
    strcpy(mat.texture, "rough");
    
    print_material(&mat);
    return 0;
}