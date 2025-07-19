/*
3_trait.md
泛型trait指针变量的类型转换
*/
#include <stdio.h>

/* In standard C, we simulate traits using function pointers in structs */

typedef struct {
    int (*convert)(void* this, void* output);
} Converter;

/* Implementation for int */
int int_convert(void* this, void* output) {
    *(int*)output = *(int*)this * 2;
    return 1;
}

/* Implementation for float */
int float_convert(void* this, void* output) {
    *(float*)output = *(float*)this * 2.0f;
    return 1;
}

int main() {
    int i = 5;
    float f = 3.5f;
    int i_out;
    float f_out;
    
    /* Create 'trait' objects */
    Converter int_converter = {.convert = int_convert};
    Converter float_converter = {.convert = float_convert};
    
    /* Use trait pointers */
    Converter* converter = &int_converter;
    converter->convert(&i, &i_out);
    printf("%d\n", i_out);
    
    converter = (Converter*)&float_converter;
    converter->convert(&f, &f_out);
    printf("%.1f\n", f_out);
    
    return 0;
}