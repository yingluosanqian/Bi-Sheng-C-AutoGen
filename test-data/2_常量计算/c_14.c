/*
2_常量计算.md
constexpr实现编译期最大公约数计算
*/
#include <stdio.h>

/* Runtime GCD calculation in C */
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    /* Must be calculated at runtime */
    int result = gcd(48, 18);
    printf("GCD of 48 and 18 is: %d\n", result);
    return 0;
}
