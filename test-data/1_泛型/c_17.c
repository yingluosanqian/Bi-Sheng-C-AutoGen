/*
1_泛型.md
泛型结构体实现坐标点，支持int, float等坐标类型
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} IntPoint;

typedef struct {
    float x;
    float y;
} FloatPoint;

void print_int_point(IntPoint *point) {
    printf("Point: (%d, %d)\n", point->x, point->y);
}

void print_float_point(FloatPoint *point) {
    printf("Point: (%.1f, %.1f)\n", point->x, point->y);
}

int main() {
    IntPoint int_point = {10, 20};
    FloatPoint float_point = {3.5, 4.5};
    
    print_int_point(&int_point);
    print_float_point(&float_point);
    
    return 0;
}