/*
8_运算符重载.md
重载<=运算符检查一个圆是否在另一个圆内
*/
#include <stdio.h>

typedef struct {
    double x;
    double y;
    double radius;
} Circle;

int circle_inside(Circle a, Circle b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double distance_sq = dx*dx + dy*dy;
    double dr = b.radius - a.radius;
    return (a.radius <= b.radius) && (distance_sq <= dr*dr);
}

int main() {
    Circle c1 = {0.0, 0.0, 2.0};
    Circle c2 = {0.0, 0.0, 4.0};
    printf("%d\n", circle_inside(c1, c2));
    return 0;
}