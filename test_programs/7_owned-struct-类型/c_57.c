/*
7_owned-struct-类型.md
创建owned struct Triangle实例并初始化三个顶点
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point a;
    Point b;
    Point c;
} Triangle;

void print_triangle(Triangle *t) {
    printf("Triangle vertices:\n");
    printf("A: (%.1f, %.1f)\n", t->a.x, t->a.y);
    printf("B: (%.1f, %.1f)\n", t->b.x, t->b.y);
    printf("C: (%.1f, %.1f)\n", t->c.x, t->c.y);
}

int main() {
    Triangle t = {
        .a = {.x = 0.0, .y = 0.0},
        .b = {.x = 1.0, .y = 0.0},
        .c = {.x = 0.5, .y = 1.0}
    };
    
    print_triangle(&t);
    return 0;
}