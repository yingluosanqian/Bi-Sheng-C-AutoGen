/*
1_泛型.md
泛型结构体实现圆形，支持不同数值类型的半径
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// In standard C, we need separate implementations for different types

// Circle with integer radius
typedef struct {
    int radius;
} CircleInt;

double circle_int_area(CircleInt* circle) {
    return M_PI * circle->radius * circle->radius;
}

double circle_int_circumference(CircleInt* circle) {
    return 2 * M_PI * circle->radius;
}

// Circle with float radius
typedef struct {
    float radius;
} CircleFloat;

double circle_float_area(CircleFloat* circle) {
    return M_PI * circle->radius * circle->radius;
}

double circle_float_circumference(CircleFloat* circle) {
    return 2 * M_PI * circle->radius;
}

// Circle with double radius
typedef struct {
    double radius;
} CircleDouble;

double circle_double_area(CircleDouble* circle) {
    return M_PI * circle->radius * circle->radius;
}

double circle_double_circumference(CircleDouble* circle) {
    return 2 * M_PI * circle->radius;
}

int main() {
    // Create circles with different radius types
    CircleInt circleInt = {5};
    CircleFloat circleFloat = {5.5f};
    CircleDouble circleDouble = {5.75};
    
    // Calculate and print areas and circumferences
    printf("Circle with int radius: %d\n", circleInt.radius);
    printf("Area: %.2f\n", circle_int_area(&circleInt));
    printf("Circumference: %.2f\n\n", circle_int_circumference(&circleInt));
    
    printf("Circle with float radius: %.2f\n", circleFloat.radius);
    printf("Area: %.2f\n", circle_float_area(&circleFloat));
    printf("Circumference: %.2f\n\n", circle_float_circumference(&circleFloat));
    
    printf("Circle with double radius: %.2f\n", circleDouble.radius);
    printf("Area: %.2f\n", circle_double_area(&circleDouble));
    printf("Circumference: %.2f\n", circle_double_circumference(&circleDouble));
    
    return 0;
}