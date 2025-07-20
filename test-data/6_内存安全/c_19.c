/*
6_内存安全.md
临时变量借用示例：创建对临时匿名变量的借用
*/
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

void print_point(const Point* p) {
    printf("Point: (%d, %d)\n", p->x, p->y);
}

int main() {
    /* In standard C, we can't directly create a pointer to a temporary */
    Point temp = {3, 4};
    const Point* p = &temp;
    print_point(p);
    return 0;
}