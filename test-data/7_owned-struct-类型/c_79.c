/*
7_owned-struct-类型.md
创建owned struct AABB实例并初始化min和max
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float min;
    float max;
} AABB;

void print_aabb(AABB *box) {
    printf("{\"min\": %f, \"max\": %f}\n", box->min, box->max);
}

int main() {
    AABB box = {.min = 0.0f, .max = 1.0f};
    print_aabb(&box);
    return 0;
}