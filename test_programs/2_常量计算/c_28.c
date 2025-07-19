/*
2_常量计算.md
使用多个type trait函数组合进行复杂类型判断
*/
#include <stdio.h>

#define IS_SIGNED_INT(T) _Generic((T)0, \
    signed char: 1, \
    short: 1, \
    int: 1, \
    long: 1, \
    long long: 1, \
    default: 0)

#define IS_UNSIGNED_INT(T) _Generic((T)0, \
    unsigned char: 1, \
    unsigned short: 1, \
    unsigned int: 1, \
    unsigned long: 1, \
    unsigned long long: 1, \
    default: 0)

#define IS_POINTER(T) _Generic((T)0, \
    void*: 1, \
    char*: 1, \
    int*: 1, \
    float*: 1, \
    double*: 1, \
    default: 0)

void check_type_int() {
    if (IS_SIGNED_INT(int) && !IS_POINTER(int)) {
        printf("signed integral\n");
    } else if (IS_UNSIGNED_INT(int) && !IS_POINTER(int)) {
        printf("unsigned integral\n");
    } else if (IS_POINTER(int)) {
        printf("pointer\n");
    } else {
        printf("other\n");
    }
}

void check_type_uint() {
    if (IS_SIGNED_INT(unsigned int) && !IS_POINTER(unsigned int)) {
        printf("signed integral\n");
    } else if (IS_UNSIGNED_INT(unsigned int) && !IS_POINTER(unsigned int)) {
        printf("unsigned integral\n");
    } else if (IS_POINTER(unsigned int)) {
        printf("pointer\n");
    } else {
        printf("other\n");
    }
}

void check_type_ptr() {
    if (IS_SIGNED_INT(int*) && !IS_POINTER(int*)) {
        printf("signed integral\n");
    } else if (IS_UNSIGNED_INT(int*) && !IS_POINTER(int*)) {
        printf("unsigned integral\n");
    } else if (IS_POINTER(int*)) {
        printf("pointer\n");
    } else {
        printf("other\n");
    }
}

int main() {
    check_type_int();
    check_type_uint();
    check_type_ptr();
    return 0;
}