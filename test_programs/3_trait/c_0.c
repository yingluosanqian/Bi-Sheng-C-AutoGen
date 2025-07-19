/*
3_trait.md
实现Printable trait，使int类型能打印自己的值
*/
#include <stdio.h>

// In standard C, we simulate polymorphism using struct with function pointers
typedef struct {
    void (*print)(void* self);
} Printable;

void int_print(void* self) {
    printf("Value: %d\n", *(int*)self);
}

void make_int_printable(int* value, Printable* printable) {
    printable->print = int_print;
}

int main() {
    int num = 42;
    Printable printable;
    
    make_int_printable(&num, &printable);
    printable.print(&num);
    
    return 0;
}
