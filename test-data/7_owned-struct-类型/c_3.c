/*
7_owned-struct-类型.md
4. Define owned struct 'Rectangle' with width and height members
*/
#include <stdio.h>
#include <stdlib.h>

struct Rectangle {
    int width;
    int height;
};

int calculate_area(struct Rectangle *rect) {
    return rect->width * rect->height;
}

int main() {
    struct Rectangle rect = {5, 10};
    int area = calculate_area(&rect);
    printf("Rectangle area: %d\n", area);
    return 0;
}