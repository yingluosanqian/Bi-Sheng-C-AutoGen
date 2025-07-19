/*
8_运算符重载.md
重载~运算符实现颜色反相
*/
#include <stdio.h>

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

Color invert_color(Color c) {
    Color inverted;
    inverted.r = 255 - c.r;
    inverted.g = 255 - c.g;
    inverted.b = 255 - c.b;
    return inverted;
}

int main() {
    Color original = {100, 150, 200};
    Color inverted = invert_color(original);
    printf("Inverted: %d, %d, %d\n", inverted.r, inverted.g, inverted.b);
    return 0;
}