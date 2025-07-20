/*
0_成员函数.md
为struct Fraction添加simplify成员函数，分数化简
*/
#include <stdio.h>
#include <stdlib.h>

// Fraction structure
struct Fraction {
    int numerator;
    int denominator;
};

// Function to find greatest common divisor (GCD)
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify a fraction
void simplify_fraction(struct Fraction* frac) {
    // Handle special cases
    if (frac->denominator == 0) {
        printf("Error: Denominator cannot be zero\n");
        return;
    }
    
    // Make sure only numerator carries the sign
    if (frac->denominator < 0) {
        frac->numerator = -frac->numerator;
        frac->denominator = -frac->denominator;
    }
    
    // Find GCD and simplify
    int divisor = gcd(frac->numerator, frac->denominator);
    if (divisor > 1) {
        frac->numerator /= divisor;
        frac->denominator /= divisor;
    }
}

int main() {
    struct Fraction frac = {24, 36};
    
    printf("Original fraction: %d/%d\n", frac.numerator, frac.denominator);
    
    simplify_fraction(&frac);
    
    printf("Simplified fraction: %d/%d\n", frac.numerator, frac.denominator);
    
    return 0;
}
