/*
7_owned-struct-类型.md
定义owned struct Point，包含x和y坐标
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

void print_point(Point *p) {
    printf("Point: (%d, %d)\n", p->x, p->y);
}

int main() {
    Point p = {.x = 10, .y = 20};
    print_point(&p);
    return 0;
}