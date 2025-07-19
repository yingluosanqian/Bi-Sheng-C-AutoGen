/*
8_运算符重载.md
重载/运算符实现分数除法
*/
#include <stdio.h>

struct Fraction {
    int numerator;
    int denominator;
};

struct Fraction divide_fractions(struct Fraction a, struct Fraction b) {
    struct Fraction result;
    result.numerator = a.numerator * b.denominator;
    result.denominator = a.denominator * b.numerator;
    return result;
}

int main() {
    struct Fraction a = {1, 2};  // 1/2
    struct Fraction b = {3, 4};  // 3/4
    struct Fraction result = divide_fractions(a, b);
    printf("Result: %d/%d\n", result.numerator, result.denominator);
    return 0;
}