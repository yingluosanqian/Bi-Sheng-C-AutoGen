/*
1_泛型.md
泛型结构体实现分数，支持不同整数类型分子分母
*/
#include <stdio.h>
#include <stdlib.h>

// Fraction structure for int type
typedef struct {
    int numerator;
    int denominator;
} FractionInt;

// Fraction structure for long type
typedef struct {
    long numerator;
    long denominator;
} FractionLong;

// Fraction structure for short type
typedef struct {
    short numerator;
    short denominator;
} FractionShort;

// Initialize fraction with int type
void init_fraction_int(FractionInt* frac, int num, int denom) {
    if (denom == 0) {
        printf("Error: Denominator cannot be zero\n");
        exit(1);
    }
    frac->numerator = num;
    frac->denominator = denom;
}

// Initialize fraction with long type
void init_fraction_long(FractionLong* frac, long num, long denom) {
    if (denom == 0) {
        printf("Error: Denominator cannot be zero\n");
        exit(1);
    }
    frac->numerator = num;
    frac->denominator = denom;
}

// Initialize fraction with short type
void init_fraction_short(FractionShort* frac, short num, short denom) {
    if (denom == 0) {
        printf("Error: Denominator cannot be zero\n");
        exit(1);
    }
    frac->numerator = num;
    frac->denominator = denom;
}

// Print fraction with int type
void print_fraction_int(FractionInt frac) {
    printf("%d/%d\n", frac.numerator, frac.denominator);
}

// Print fraction with long type
void print_fraction_long(FractionLong frac) {
    printf("%ld/%ld\n", frac.numerator, frac.denominator);
}

// Print fraction with short type
void print_fraction_short(FractionShort frac) {
    printf("%hd/%hd\n", frac.numerator, frac.denominator);
}

int main() {
    // Create and initialize fractions with different integer types
    FractionInt frac_int;
    init_fraction_int(&frac_int, 1, 2);
    
    FractionLong frac_long;
    init_fraction_long(&frac_long, 3L, 4L);
    
    FractionShort frac_short;
    init_fraction_short(&frac_short, 5, 6);
    
    // Print all fractions
    printf("Int fraction: ");
    print_fraction_int(frac_int);
    
    printf("Long fraction: ");
    print_fraction_long(frac_long);
    
    printf("Short fraction: ");
    print_fraction_short(frac_short);
    
    return 0;
}