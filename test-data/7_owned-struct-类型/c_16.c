/*
7_owned-struct-类型.md
定义owned struct Rectangle，包含width和height成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
} Rectangle;

int calculate_area(Rectangle *rect) {
    return rect->width * rect->height;
}

int main() {
    Rectangle rect = {5, 10};
    int area = calculate_area(&rect);
    printf("Rectangle area: %d\n", area);
    return 0;
}