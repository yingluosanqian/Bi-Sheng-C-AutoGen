/*
8_运算符重载.md
重载&运算符实现掩码生成
*/
#include <stdio.h>

struct Maskable {
    unsigned int value;
};

struct Maskable mask_and(struct Maskable a, struct Maskable b) {
    struct Maskable result;
    result.value = a.value & b.value;
    return result;
}

int main() {
    struct Maskable a = {0xFF00FF00};
    struct Maskable b = {0x00FFFF00};
    struct Maskable c = mask_and(a, b);
    printf("Result: 0x%08X\n", c.value);
    return 0;
}