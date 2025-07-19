/*
8_运算符重载.md
重载~运算符实现逻辑非
*/
#include <stdio.h>

struct BoolWrapper {
    int value; // Using int to represent boolean (0=false, non-zero=true)
};

int logical_not(int val) {
    return val == 0 ? 1 : 0;
}

int main() {
    struct BoolWrapper b = {0}; // false
    int result = logical_not(b.value);
    printf("%d\n", result); // Output: 1 (true)
    return 0;
}