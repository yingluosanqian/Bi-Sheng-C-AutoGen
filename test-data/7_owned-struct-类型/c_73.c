/*
7_owned-struct-类型.md
创建owned struct Quaternion实例并初始化四元数
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double w;
    double x;
    double y;
    double z;
} Quaternion;

void print_quaternion(const Quaternion *q) {
    printf("Quaternion: w=%.2f, x=%.2f, y=%.2f, z=%.2f\n", q->w, q->x, q->y, q->z);
}

int main() {
    Quaternion q = {1.0, 0.0, 1.0, 0.0};
    print_quaternion(&q);
    return 0;
}