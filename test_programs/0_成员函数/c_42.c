/*
0_成员函数.md
为struct Stack添加push成员函数，入栈操作
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

struct Stack {
    int data[MAX_SIZE];
    int top;
};

void init_stack(struct Stack* stack) {
    stack->top = -1;
}

int push_stack(struct Stack* stack, int value) {
    if (stack->top >= MAX_SIZE - 1) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = value;
    return 1; // Success
}

void print_stack(struct Stack* stack) {
    printf("Stack contents: ");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    init_stack(&stack);
    
    push_stack(&stack, 10);
    push_stack(&stack, 20);
    push_stack(&stack, 30);
    
    print_stack(&stack);
    
    return 0;
}