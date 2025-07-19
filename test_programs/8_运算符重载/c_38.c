/*
8_运算符重载.md
重载/运算符实现单位转换
*/
#include <stdio.h>

struct Distance {
    int meters;
    int centimeters;
};

struct Distance add_distances(struct Distance d1, struct Distance d2) {
    struct Distance result;
    int total_cm = (d1.meters * 100 + d1.centimeters) + (d2.meters * 100 + d2.centimeters);
    result.meters = total_cm / 100;
    result.centimeters = total_cm % 100;
    return result;
}

int main() {
    struct Distance d1 = {1, 80};  // 1m 80cm
    struct Distance d2 = {0, 30};  // 30cm
    
    struct Distance total = add_distances(d1, d2);
    printf("Total: %d meters and %d centimeters\n", total.meters, total.centimeters);
    return 0;
}