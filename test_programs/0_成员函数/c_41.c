/*
0_成员函数.md
为struct Fraction添加add成员函数，分数加法
*/
#include <stdio.h>
#include <stdlib.h>

struct Fraction {
    int numerator;
    int denominator;
};

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct Fraction add_fraction(struct Fraction *f1, struct Fraction *f2) {
    struct Fraction result;
    result.numerator = f1->numerator * f2->denominator + f2->numerator * f1->denominator;
    result.denominator = f1->denominator * f2->denominator;
    
    int g = gcd(abs(result.numerator), abs(result.denominator));
    result.numerator /= g;
    result.denominator /= g;
    
    return result;
}

int main() {
    struct Fraction f1 = {1, 3};
    struct Fraction f2 = {1, 6};
    
    struct Fraction result = add_fraction(&f1, &f2);
    
    printf("%d/%d\n", result.numerator, result.denominator);
    
    return 0;
}