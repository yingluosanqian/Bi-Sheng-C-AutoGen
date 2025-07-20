/*
0_成员函数.md
为struct Stack添加pop成员函数，出栈操作
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int top;
    int capacity;
} Stack;

Stack* create_stack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->data = (int*)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push_stack(Stack *stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

int pop_stack(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return -1;
}

int is_empty_stack(Stack *stack) {
    return stack->top == -1;
}

void destroy_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

int main() {
    Stack *stack = create_stack(5);
    
    push_stack(stack, 10);
    push_stack(stack, 20);
    push_stack(stack, 30);
    
    while (!is_empty_stack(stack)) {
        printf("%d\n", pop_stack(stack));
    }
    
    destroy_stack(stack);
    return 0;
}