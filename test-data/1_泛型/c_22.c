/*
1_泛型.md
常量泛型实现固定容量的栈，容量大小可配置
*/
#include <stdio.h>
#include <stdlib.h>

/* Stack with capacity 5 */
struct Stack5 {
    int data[5];
    int top;
};

void init_stack5(struct Stack5 *stack) {
    stack->top = -1;
}

int push_stack5(struct Stack5 *stack, int value) {
    if (stack->top >= 4) {
        return 0; /* Stack overflow */
    }
    stack->data[++stack->top] = value;
    return 1;
}

int pop_stack5(struct Stack5 *stack, int *value) {
    if (stack->top < 0) {
        return 0; /* Stack underflow */
    }
    *value = stack->data[stack->top--];
    return 1;
}

/* Stack with capacity 10 */
struct Stack10 {
    int data[10];
    int top;
};

void init_stack10(struct Stack10 *stack) {
    stack->top = -1;
}

int push_stack10(struct Stack10 *stack, int value) {
    if (stack->top >= 9) {
        return 0; /* Stack overflow */
    }
    stack->data[++stack->top] = value;
    return 1;
}

int pop_stack10(struct Stack10 *stack, int *value) {
    if (stack->top < 0) {
        return 0; /* Stack underflow */
    }
    *value = stack->data[stack->top--];
    return 1;
}

int main() {
    struct Stack5 stack5;
    struct Stack10 stack10;
    int value;
    
    init_stack5(&stack5);
    init_stack10(&stack10);
    
    /* Test stack with capacity 5 */
    push_stack5(&stack5, 10);
    push_stack5(&stack5, 20);
    push_stack5(&stack5, 30);
    
    pop_stack5(&stack5, &value);
    printf("Popped from stack5: %d\n", value);
    
    /* Test stack with capacity 10 */
    push_stack10(&stack10, 100);
    push_stack10(&stack10, 200);
    push_stack10(&stack10, 300);
    
    pop_stack10(&stack10, &value);
    printf("Popped from stack10: %d\n", value);
    
    return 0;
}