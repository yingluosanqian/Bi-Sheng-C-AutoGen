/*
0_成员函数.md
为struct Rectangle添加area成员函数，计算矩形面积
*/
#include <stdio.h>
#include <stdlib.h>

struct Rectangle {
    double width;
    double height;
};

double calculate_area(struct Rectangle* rect) {
    return rect->width * rect->height;
}

int main() {
    struct Rectangle rect = {5.0, 3.0};
    double area = calculate_area(&rect);
    printf("%.1f\n", area);
    return 0;
}