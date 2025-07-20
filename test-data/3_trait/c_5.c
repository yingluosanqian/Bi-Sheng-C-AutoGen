/*
3_trait.md
为struct Circle和Rectangle实现Shape trait计算面积
*/
#include <stdio.h>
#include <math.h>

// Function pointer types
typedef double (*AreaFunc)(void*);

// Shape "interface" simulated with struct and function pointers
struct Shape {
    void *self;
    AreaFunc get_area;
};

// Circle implementation
double circle_area(void *this) {
    double radius = *(double*)this;
    return M_PI * radius * radius;
}

// Rectangle implementation
double rectangle_area(void *this) {
    double *dims = (double*)this;
    return dims[0] * dims[1];
}

void print_area(struct Shape shape) {
    double area = shape.get_area(shape.self);
    printf("Area: %.2f\n", area);
}

int main() {
    // Circle
    double radius = 5.0;
    struct Shape circle = {&radius, circle_area};
    
    // Rectangle
    double dimensions[2] = {4.0, 6.0};
    struct Shape rectangle = {dimensions, rectangle_area};
    
    print_area(circle);    // Area: 78.54
    print_area(rectangle); // Area: 24.00
    
    return 0;
}
