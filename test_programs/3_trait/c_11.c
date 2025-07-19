/*
3_trait.md
定义泛型trait Converter<T>，为int类型实现convert方法转换为其他类型
*/
#include <stdio.h>
#include <stdlib.h>

/* In standard C, we use function pointers to simulate polymorphism */
typedef struct {
    void* (*convert)(void*);
} Converter;

void* int_to_float(void* this) {
    int* val = (int*)this;
    float* result = malloc(sizeof(float));
    *result = (float)*val;
    return result;
}

void* int_to_string(void* this) {
    int* val = (int*)this;
    char* result = malloc(32);
    sprintf(result, "%d", *val);
    return result;
}

int main() {
    int value = 42;
    
    /* Simulate trait implementation */
    Converter int_converter = {
        .convert = int_to_float
    };
    
    float* converted = (float*)int_converter.convert(&value);
    printf("%f\n", *converted);
    free(converted);
    
    /* Change converter behavior */
    int_converter.convert = int_to_string;
    char* str = (char*)int_converter.convert(&value);
    printf("%s\n", str);
    free(str);
    
    return 0;
}