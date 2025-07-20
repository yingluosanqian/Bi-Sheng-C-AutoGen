/*
6_内存安全.md
安全区枚举示例：定义类型安全的枚举
*/
#include <stdio.h>

/* Standard C enum - essentially just integers */
typedef enum {
    RED,
    GREEN,
    BLUE
} Color;

void print_color(Color c) {
    switch(c) {
        case RED: printf("Red\n"); break;
        case GREEN: printf("Green\n"); break;
        case BLUE: printf("Blue\n"); break;
    }
}

int main() {
    Color c = GREEN;
    print_color(c);
    
    /* No type safety - can assign any integer */
    c = 42;  /* No compiler warning */
    print_color(c);  /* Undefined behavior */
    
    return 0;
}