/*
2_常量计算.md
泛型结构体成员函数中使用type trait判断类型属性
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*print_type_info)(void);
} TypeChecker;

void print_int_info(void) {
    printf("Type: integral\n");
    printf("Size: %zu bytes\n", sizeof(int));
    printf("Signed: yes\n");
}

void print_float_info(void) {
    printf("Type: floating point\n");
    printf("Size: %zu bytes\n", sizeof(float));
    printf("Signed: yes\n");
}

void print_pointer_info(void) {
    printf("Type: pointer\n");
    printf("Size: %zu bytes\n", sizeof(void*));
    printf("Signed: no\n");
}

int main() {
    TypeChecker int_checker = {print_int_info};
    TypeChecker float_checker = {print_float_info};
    TypeChecker pointer_checker = {print_pointer_info};
    
    int_checker.print_type_info();
    float_checker.print_type_info();
    pointer_checker.print_type_info();
    
    return 0;
}