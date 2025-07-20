/*
6_内存安全.md
结构体借用示例：结构体包含借用指针成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int* pointer;  // Regular pointer in C
} Container;

void print_container(Container* c) {
    printf("Value: %d, Pointer: %d\n", c->value, *(c->pointer));
}

int main(void) {
    int num = 42;
    Container c = {
        .value = 10,
        .pointer = &num
    };
    
    print_container(&c);
    return 0;
}