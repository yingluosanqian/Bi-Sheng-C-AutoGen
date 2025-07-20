/*
0_成员函数.md
为struct Point添加print成员函数，打印坐标点
*/
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void print_point(struct Point* point) {
    printf("Point(%d, %d)\n", point->x, point->y);
}

int main() {
    struct Point p = {3, 4};
    print_point(&p);
    return 0;
}