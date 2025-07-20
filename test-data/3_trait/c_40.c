/*
3_trait.md
泛型trait Calculator实现基本数学运算
*/
#include <stdio.h>
#include <stdlib.h>

// Function pointer types for calculator operations
typedef int (*IntBinaryOp)(int, int);
typedef float (*FloatBinaryOp)(float, float);

// Calculator "trait" simulation in C
struct IntCalculator {
    IntBinaryOp add;
    IntBinaryOp subtract;
    IntBinaryOp multiply;
    IntBinaryOp divide;
};

struct FloatCalculator {
    FloatBinaryOp add;
    FloatBinaryOp subtract;
    FloatBinaryOp multiply;
    FloatBinaryOp divide;
};

// Operation implementations
int int_add(int a, int b) { return a + b; }
int int_sub(int a, int b) { return a - b; }
int int_mul(int a, int b) { return a * b; }
int int_div(int a, int b) { return a / b; }

float float_add(float a, float b) { return a + b; }
float float_sub(float a, float b) { return a - b; }
float float_mul(float a, float b) { return a * b; }
float float_div(float a, float b) { return a / b; }

// Initialize calculator instances
struct IntCalculator int_calc = {
    .add = int_add,
    .subtract = int_sub,
    .multiply = int_mul,
    .divide = int_div
};

struct FloatCalculator float_calc = {
    .add = float_add,
    .subtract = float_sub,
    .multiply = float_mul,
    .divide = float_div
};

int main() {
    // Using integer calculator
    int a = 10, b = 3;
    printf("Integer operations:\n");
    printf("%d + %d = %d\n", a, b, int_calc.add(a, b));
    printf("%d - %d = %d\n", a, b, int_calc.subtract(a, b));
    printf("%d * %d = %d\n", a, b, int_calc.multiply(a, b));
    printf("%d / %d = %d\n", a, b, int_calc.divide(a, b));

    // Using float calculator
    float x = 10.5f, y = 3.2f;
    printf("\nFloat operations:\n");
    printf("%.2f + %.2f = %.2f\n", x, y, float_calc.add(x, y));
    printf("%.2f - %.2f = %.2f\n", x, y, float_calc.subtract(x, y));
    printf("%.2f * %.2f = %.2f\n", x, y, float_calc.multiply(x, y));
    printf("%.2f / %.2f = %.2f\n", x, y, float_calc.divide(x, y));

    return 0;
}
