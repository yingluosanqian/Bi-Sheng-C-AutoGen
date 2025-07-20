/*
3_trait.md
结构体实现多个不同trait的组合使用
*/
#include <stdio.h>

/* In standard C, we simulate traits using function pointers in structs */
typedef struct {
    void (*print)(void*);
    int (*calculate)(void*);
} Traits;

typedef struct {
    int value;
    Traits traits;
} MyStruct;

void my_struct_print(void* this) {
    MyStruct* s = (MyStruct*)this;
    printf("Value: %d\n", s->value);
}

int my_struct_calculate(void* this) {
    MyStruct* s = (MyStruct*)this;
    return s->value * 2;
}

void init_my_struct(MyStruct* s, int value) {
    s->value = value;
    s->traits.print = my_struct_print;
    s->traits.calculate = my_struct_calculate;
}

int main() {
    MyStruct s;
    init_my_struct(&s, 42);
    
    s.traits.print(&s);
    int result = s.traits.calculate(&s);
    printf("Calculation result: %d\n", result);
    
    return 0;
}