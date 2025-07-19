/*
8_运算符重载.md
重载&运算符实现位掩码过滤
*/
#include <stdio.h>

typedef struct {
    unsigned int flags;
} Bitmask;

Bitmask bitwise_and(Bitmask a, Bitmask b) {
    Bitmask result;
    result.flags = a.flags & b.flags;
    return result;
}

int main() {
    Bitmask mask1 = {.flags = 0x0F};  // 00001111
    Bitmask mask2 = {.flags = 0x33};  // 00110011
    Bitmask result = bitwise_and(mask1, mask2);
    printf("%u\n", result.flags);  // Output: 3 (00000011)
    return 0;
}