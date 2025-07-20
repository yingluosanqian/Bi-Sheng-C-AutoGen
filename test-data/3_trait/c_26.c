/*
3_trait.md
为struct Color实现Mixable trait支持颜色混合
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

typedef struct {
    Color* (*mix)(Color* this, Color* other);
} Mixable;

Color* Color_mix(Color* this, Color* other) {
    Color* result = malloc(sizeof(Color));
    result->r = (this->r + other->r) / 2;
    result->g = (this->g + other->g) / 2;
    result->b = (this->b + other->b) / 2;
    return result;
}

void print_color(Color* color) {
    printf("RGB: (%d, %d, %d)\n", color->r, color->g, color->b);
}

int main() {
    Color red = {255, 0, 0};
    Color blue = {0, 0, 255};
    
    Mixable mixable_red = {Color_mix};
    Color* purple = mixable_red.mix(&red, &blue);
    
    printf("Red: ");
    print_color(&red);
    printf("Blue: ");
    print_color(&blue);
    printf("Purple (mixed): ");
    print_color(purple);
    
    free(purple);
    return 0;
}
