/*
7_owned-struct-类型.md
1. Define an owned struct 'Point' with x and y coordinates
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

void print_point(Point* p) {
    printf("Point: (%d, %d)\n", p->x, p->y);
}

int main() {
    Point p = {.x = 10, .y = 20};
    print_point(&p);
    return 0;
}