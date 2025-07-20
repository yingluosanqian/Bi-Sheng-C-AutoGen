/*
7_owned-struct-类型.md
定义owned struct Cylinder，包含radius和height
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double radius;
    double height;
} Cylinder;

double calculate_volume(const Cylinder *cyl) {
    return 3.141592653589793 * cyl->radius * cyl->radius * cyl->height;
}

int main() {
    Cylinder cyl = {.radius = 2.5, .height = 10.0};
    double volume = calculate_volume(&cyl);
    printf("Cylinder volume: %.2f\n", volume);
    return 0;
}