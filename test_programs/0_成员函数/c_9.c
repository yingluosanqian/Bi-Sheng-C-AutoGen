/*
0_成员函数.md
为struct Circle添加area成员函数，计算圆形面积
*/
#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159

struct Circle {
    double radius;
};

double calculate_area(struct Circle* circle) {
    return PI * circle->radius * circle->radius;
}

int main() {
    struct Circle circle = {5.0};
    double area = calculate_area(&circle);
    printf("Circle area: %.2f\n", area);
    return 0;
}