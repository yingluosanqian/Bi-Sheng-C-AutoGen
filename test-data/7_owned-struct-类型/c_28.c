/*
7_owned-struct-类型.md
定义owned struct Color，包含red、green和blue成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Color {
    int red;
    int green;
    int blue;
};

void print_color(struct Color *c) {
    printf("Color: R=%d, G=%d, B=%d\n", c->red, c->green, c->blue);
}

int main() {
    struct Color c = {255, 128, 0};
    print_color(&c);
    return 0;
}