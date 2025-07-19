/*
8_运算符重载.md
重载<<运算符实现数据压缩
*/
#include <stdio.h>

int compress_data(int data, int shift_bits) {
    return (data >> shift_bits) << shift_bits;
}

int main() {
    int original = 100;  // Binary: 01100100
    int shift = 2;       // Zero out 2 lowest bits
    
    int compressed = compress_data(original, shift);
    printf("%d\n", compressed);  // Output: 96 (binary: 01100000)
    return 0;
}