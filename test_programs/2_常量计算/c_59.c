/*
2_常量计算.md
constexpr函数计算编译时几何运算
*/
#include <stdio.h>

#define PI 3.14159

/* Standard C cannot guarantee compile-time calculation */
int calculate_circle_area(int radius) {
    return (int)(PI * radius * radius);
}

int main() {
    int radius = 5;
    int area = calculate_circle_area(radius);
    printf("%d\n", area);
    return 0;
}