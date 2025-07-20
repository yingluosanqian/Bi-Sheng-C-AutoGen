/*
7_owned-struct-类型.md
创建owned struct Color实例并初始化RGB值
*/
#include <stdio.h>
#include <stdlib.h>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

void print_color(struct Color *c) {
    printf("R: %d, G: %d, B: %d\n", c->r, c->g, c->b);
}

int main() {
    struct Color my_color = {255, 128, 0};
    print_color(&my_color);
    return 0;
}