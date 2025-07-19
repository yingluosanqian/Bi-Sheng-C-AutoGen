/*
7_owned-struct-类型.md
32. Create owned struct 'Pixel' with x, y coordinates and color
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    int color;
} Pixel;

void print_pixel(Pixel *p) {
    printf("Pixel at (%d, %d) with color %d\n", p->x, p->y, p->color);
}

int main() {
    Pixel p = {10, 20, 0xFF0000};
    print_pixel(&p);
    return 0;
}