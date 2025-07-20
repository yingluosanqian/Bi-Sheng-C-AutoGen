/*
7_owned-struct-类型.md
创建owned struct Vector2D实例并初始化x和y
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Vector2D;

void print_vector(Vector2D *v) {
    printf("{\"x\": %d, \"y\": %d}\n", v->x, v->y);
}

int main() {
    Vector2D vec = {.x = 10, .y = 20};
    print_vector(&vec);
    return 0;
}