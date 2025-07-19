/*
8_运算符重载.md
重载+运算符实现正数验证
*/
#include <stdio.h>
#include <stdbool.h>

struct PositiveNumber {
    int value;
};

struct PositiveNumber create_positive(int val) {
    if (val <= 0) {
        printf("Error: Value must be positive! Using default 1.\n");
        return (struct PositiveNumber){1};
    }
    return (struct PositiveNumber){val};
}

struct PositiveNumber add_positives(struct PositiveNumber a, struct PositiveNumber b) {
    int sum = a.value + b.value;
    return create_positive(sum);
}

int main() {
    struct PositiveNumber a = create_positive(5);
    struct PositiveNumber b = create_positive(-3); // Will be corrected to 1
    
    // In standard C, we must explicitly call the add function
    struct PositiveNumber result = add_positives(a, b);
    
    printf("Result: %d\n", result.value); // Should print 6 (5 + 1)
    return 0;
}
