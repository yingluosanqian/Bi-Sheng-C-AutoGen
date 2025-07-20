/*
7_owned-struct-类型.md
定义owned struct Quaternion，包含x、y、z和w成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
    double z;
    double w;
} Quaternion;

void print_quaternion(const Quaternion *q) {
    printf("Quaternion: x=%.2f, y=%.2f, z=%.2f, w=%.2f\n", q->x, q->y, q->z, q->w);
}

int main() {
    Quaternion q = {1.0, 2.0, 3.0, 4.0};
    print_quaternion(&q);
    return 0;
}