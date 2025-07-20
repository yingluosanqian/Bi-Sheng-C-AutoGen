/*
7_owned-struct-类型.md
16. Define owned struct 'Color' with RGB components
*/
#include <stdio.h>
#include <stdlib.h>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

void print_color(struct Color *c) {
    printf("RGB: (%d, %d, %d)\n", c->r, c->g, c->b);
}

int main() {
    struct Color my_color = {255, 128, 0};
    print_color(&my_color);
    return 0;
}