/*
2_常量计算.md
constexpr if处理不同整数类型的统一接口
*/
#include <stdio.h>
#include <stdlib.h>

void print_int_info(int value) {
    printf("Value: %d, Size: %zu bytes, Type: signed integer\n", value, sizeof(int));
}

void print_uint_info(unsigned int value) {
    printf("Value: %u, Size: %zu bytes, Type: unsigned integer\n", value, sizeof(unsigned int));
}

void print_char_info(char value) {
    printf("Value: %d, Size: %zu bytes, Type: character\n", value, sizeof(char));
}

void print_short_info(short value) {
    printf("Value: %d, Size: %zu bytes, Type: short integer\n", value, sizeof(short));
}

int main() {
    int a = 42;
    unsigned int b = 100;
    char c = 65;
    short d = 1000;
    
    print_int_info(a);
    print_uint_info(b);
    print_char_info(c);
    print_short_info(d);
    
    return 0;
}