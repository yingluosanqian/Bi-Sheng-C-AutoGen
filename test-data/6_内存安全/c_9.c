/*
6_内存安全.md
安全区内使用borrow指针作为函数参数避免所有权转移
*/
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void move_point(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

int main() {
    Point p = {10, 20};
    move_point(&p, 5, -3);
    printf("(%d, %d)\n", p.x, p.y);
    return 0;
}