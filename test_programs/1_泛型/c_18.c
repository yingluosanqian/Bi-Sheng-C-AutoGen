/*
1_泛型.md
泛型结构体实现矩形，支持不同数值类型的长宽
*/
#include <stdio.h>

struct IntRectangle {
    int width;
    int height;
};

struct FloatRectangle {
    float width;
    float height;
};

int int_area(struct IntRectangle *rect) {
    return rect->width * rect->height;
}

float float_area(struct FloatRectangle *rect) {
    return rect->width * rect->height;
}

int main() {
    struct IntRectangle int_rect = {10, 20};
    struct FloatRectangle float_rect = {10.5, 20.5};
    
    int int_result = int_area(&int_rect);
    float float_result = float_area(&float_rect);
    
    printf("Int rectangle area: %d\n", int_result);
    printf("Float rectangle area: %.1f\n", float_result);
    
    return 0;
}