/*
2_常量计算.md
constexpr if在数值计算中的分支优化
*/
#include <stdio.h>

int power_of_two(int exponent) {
    if (exponent == 0) {
        return 1;
    } else if (exponent == 1) {
        return 2;
    } else if (exponent == 2) {
        return 4;
    } else if (exponent == 3) {
        return 8;
    } else {
        int result = 1;
        for (int i = 0; i < exponent; i++) {
            result *= 2;
        }
        return result;
    }
}

int main() {
    printf("%d\n", power_of_two(3));
    return 0;
}