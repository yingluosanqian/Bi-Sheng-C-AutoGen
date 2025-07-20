/*
8_运算符重载.md
重载+运算符实现两个二维坐标点相加
*/
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

Point add_points(Point a, Point b) {
    Point result = {a.x + b.x, a.y + b.y};
    return result;
}

int main() {
    Point p1 = {1, 2};
    Point p2 = {3, 4};
    Point p3 = add_points(p1, p2);
    printf("%d %d\n", p3.x, p3.y);
    return 0;
}