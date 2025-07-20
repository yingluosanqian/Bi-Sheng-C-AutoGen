/*
7_owned-struct-类型.md
创建owned struct Fraction实例并初始化分子分母
*/
#include <stdio.h>
#include <stdlib.h>

struct Fraction {
    int numerator;
    int denominator;
};

void print_fraction(struct Fraction f) {
    printf("Fraction: %d/%d\n", f.numerator, f.denominator);
}

int main() {
    struct Fraction f = {3, 4};
    print_fraction(f);
    return 0;
}