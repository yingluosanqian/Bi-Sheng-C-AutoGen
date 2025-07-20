/*
3_trait.md
泛型trait Stack<T>为IntStack结构体实现push和pop方法
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct IntStack {
    int *data;
    int top;
    int capacity;
} IntStack;

void IntStack_init(IntStack *stack, int capacity) {
    stack->data = (int *)malloc(capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = capacity;
}

int IntStack_push(IntStack *stack, int value) {
    if (stack->top >= stack->capacity - 1) return 0;
    stack->data[++stack->top] = value;
    return 1;
}

int IntStack_pop(IntStack *stack, int *value) {
    if (stack->top < 0) return 0;
    *value = stack->data[stack->top--];
    return 1;
}

int main() {
    IntStack stack;
    IntStack_init(&stack, 10);
    
    int val;
    IntStack_push(&stack, 42);
    IntStack_pop(&stack, &val);
    
    printf("%d\n", val);
    free(stack.data);
    return 0;
}