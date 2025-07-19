/*
0_成员函数.md
为struct Stack添加is_empty成员函数，判断栈是否为空
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// Initialize the stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Push an element to the stack
void push(Stack* stack, int value) {
    if (stack->top < MAX_SIZE - 1) {
        stack->items[++(stack->top)] = value;
    } else {
        printf("Stack overflow\n");
    }
}

// Pop an element from the stack
int pop(Stack* stack) {
    if (stack->top >= 0) {
        return stack->items[(stack->top)--];
    } else {
        printf("Stack underflow\n");
        return -1;
    }
}

// Check if the stack is empty
int is_empty(Stack* stack) {
    return stack->top == -1;
}

int main() {
    Stack myStack;
    initStack(&myStack);
    
    // Check if the stack is initially empty
    printf("Is stack empty? %s\n", is_empty(&myStack) ? "Yes" : "No");
    
    // Push some elements
    push(&myStack, 10);
    push(&myStack, 20);
    push(&myStack, 30);
    
    // Check if the stack is empty after pushing elements
    printf("Is stack empty? %s\n", is_empty(&myStack) ? "Yes" : "No");
    
    // Pop all elements
    while (!is_empty(&myStack)) {
        printf("Popped: %d\n", pop(&myStack));
    }
    
    // Check if the stack is empty after popping all elements
    printf("Is stack empty? %s\n", is_empty(&myStack) ? "Yes" : "No");
    
    return 0;
}
