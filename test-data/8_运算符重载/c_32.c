/*
8_运算符重载.md
重载^运算符实现数据校验
*/
#include <stdio.h>

typedef struct {
    int value;
    int checksum;
} Data;

Data compute_checksum(Data d, int key) {
    Data result = d;
    result.checksum = d.value ^ key;
    return result;
}

int main() {
    Data input = { .value = 0x1234 };
    int validation_key = 0x55;
    
    Data validated = compute_checksum(input, validation_key);
    
    printf("value: %d\nchecksum: %d\n", validated.value, validated.checksum);
    return 0;
}