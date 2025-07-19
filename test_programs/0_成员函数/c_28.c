/*
0_成员函数.md
为struct Color添加to_hex成员函数，转为16进制颜色值
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

// Standalone function in C
char* color_to_hex(const Color* color) {
    char* hex = malloc(8); // #RRGGBB + null terminator
    if (hex) {
        sprintf(hex, "#%02X%02X%02X", color->r, color->g, color->b);
    }
    return hex;
}

int main() {
    Color c = {255, 128, 0};
    char* hex = color_to_hex(&c);
    
    if (hex) {
        printf("Color hex: %s\n", hex);
        free(hex);
    }
    
    return 0;
}
