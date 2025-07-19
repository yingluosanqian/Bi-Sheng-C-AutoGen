/*
7_owned-struct-类型.md
定义owned struct AABB，包含min和max点
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float min[3];
    float max[3];
} AABB;

void print_aabb(const AABB *box) {
    printf("Min: (%.2f, %.2f, %.2f)\n", box->min[0], box->min[1], box->min[2]);
    printf("Max: (%.2f, %.2f, %.2f)\n", box->max[0], box->max[1], box->max[2]);
}

int main() {
    AABB box = {
        .min = {0.0f, 0.0f, 0.0f},
        .max = {1.0f, 1.0f, 1.0f}
    };
    
    print_aabb(&box);
    return 0;
}