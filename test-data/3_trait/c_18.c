/*
3_trait.md
trait指针变量在函数间传递作为参数和返回值
*/
#include <stdio.h>
#include <stdlib.h>

/* Simulating trait-like behavior in C using function pointers */
struct Printable {
    void (*print)(void*);
};

void int_print(void* this) {
    printf("%d\n", *(int*)this);
}

void float_print(void* this) {
    printf("%f\n", *(float*)this);
}

struct Printable* make_printable_int(int* value) {
    struct Printable* p = malloc(sizeof(struct Printable));
    p->print = int_print;
    return p;
}

struct Printable* make_printable_float(float* value) {
    struct Printable* p = malloc(sizeof(struct Printable));
    p->print = float_print;
    return p;
}

void print_value(struct Printable* p, void* value) {
    p->print(value);
}

struct Printable* get_printer(struct Printable* p) {
    return p;
}

int main() {
    int i = 42;
    float f = 3.14;
    
    struct Printable* int_printer = make_printable_int(&i);
    struct Printable* float_printer = make_printable_float(&f);
    
    print_value(int_printer, &i);
    print_value(float_printer, &f);
    
    struct Printable* p = get_printer(int_printer);
    p->print(&i);
    
    free(int_printer);
    free(float_printer);
    return 0;
}