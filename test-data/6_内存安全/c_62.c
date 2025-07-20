/*
6_内存安全.md
安全区数学运算示例：防止数值溢出
*/
#include <stdio.h>
#include <limits.h>

int safe_add(int a, int b) {
    if ((b > 0 && a > INT_MAX - b) ||
        (b < 0 && a < INT_MIN - b)) {
        return 0; // Overflow occurred
    }
    return a + b;
}

int main() {
    int a = INT_MAX - 5;
    int b = 10;
    int result = safe_add(a, b);
    printf("%d\n", result);
    return 0;
}