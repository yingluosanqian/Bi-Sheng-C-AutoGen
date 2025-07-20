/*
8_运算符重载.md
重载^运算符实现位交换
*/
#include <stdio.h>

typedef struct {
    int value;
} IntWrapper;

int main() {
    IntWrapper a = {10};
    IntWrapper b = {20};
    
    // Manual XOR swap
    a.value = a.value ^ b.value;
    b.value = b.value ^ a.value;
    a.value = a.value ^ b.value;
    
    printf("a=%d b=%d", a.value, b.value);
    return 0;
}