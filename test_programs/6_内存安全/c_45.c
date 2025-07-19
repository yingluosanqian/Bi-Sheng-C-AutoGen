/*
6_内存安全.md
安全区switch示例：类型安全的switch语句
*/
#include <stdio.h>

typedef enum { RED, GREEN, BLUE } Color;

void print_color(Color c) {
    switch (c) {
        case RED:   printf("Red\n"); break;
        case GREEN: printf("Green\n"); break;
        case BLUE:  printf("Blue\n"); break;
        // No default case - potential bug if new color is added
    }
}

int main() {
    print_color(RED);
    print_color(GREEN);
    print_color(BLUE);
    return 0;
}