/*
0_成员函数.md
为struct Color添加to_hex成员函数，转换为十六进制颜色值
*/
#include <stdio.h>
#include <stdlib.h>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

// In standard C, we need a separate function that takes the struct as a parameter
char* color_to_hex(const struct Color* color) {
    char* hex_string = (char*)malloc(8 * sizeof(char)); // #RRGGBB\0
    if (hex_string == NULL) {
        return NULL;
    }
    
    sprintf(hex_string, "#%02X%02X%02X", color->r, color->g, color->b);
    return hex_string;
}

int main() {
    struct Color red = {255, 0, 0};
    struct Color green = {0, 255, 0};
    struct Color blue = {0, 0, 255};
    
    char* red_hex = color_to_hex(&red);
    char* green_hex = color_to_hex(&green);
    char* blue_hex = color_to_hex(&blue);
    
    printf("Red: %s\n", red_hex);
    printf("Green: %s\n", green_hex);
    printf("Blue: %s\n", blue_hex);
    
    free(red_hex);
    free(green_hex);
    free(blue_hex);
    
    return 0;
}