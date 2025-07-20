/*
1_泛型.md
泛型结构体实现简单的栈结构，支持任意类型元素
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In standard C, we need to create a separate stack for each type
// or use void pointers with type casting (which sacrifices type safety)

// Stack implementation for integers
typedef struct {
    int* data;
    int top;
    int capacity;
} IntStack;

IntStack* int_stack_create(int capacity) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    stack->data = (int*)malloc(sizeof(int) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int int_stack_push(IntStack* stack, int value) {
    if (stack->top >= stack->capacity - 1) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = value;
    return 1;
}

int int_stack_pop(IntStack* stack, int* value) {
    if (stack->top < 0) {
        return 0; // Stack underflow
    }
    *value = stack->data[stack->top--];
    return 1;
}

void int_stack_destroy(IntStack* stack) {
    free(stack->data);
    free(stack);
}

// Stack implementation for doubles (note the duplication)
typedef struct {
    double* data;
    int top;
    int capacity;
} DoubleStack;

DoubleStack* double_stack_create(int capacity) {
    DoubleStack* stack = (DoubleStack*)malloc(sizeof(DoubleStack));
    stack->data = (double*)malloc(sizeof(double) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

int double_stack_push(DoubleStack* stack, double value) {
    if (stack->top >= stack->capacity - 1) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = value;
    return 1;
}

int double_stack_pop(DoubleStack* stack, double* value) {
    if (stack->top < 0) {
        return 0; // Stack underflow
    }
    *value = stack->data[stack->top--];
    return 1;
}

void double_stack_destroy(DoubleStack* stack) {
    free(stack->data);
    free(stack);
}

int main() {
    // Integer stack
    IntStack* int_stack = int_stack_create(5);
    int_stack_push(int_stack, 10);
    int_stack_push(int_stack, 20);
    int_stack_push(int_stack, 30);
    
    int int_val;
    int_stack_pop(int_stack, &int_val);
    printf("Popped integer: %d\n", int_val);
    int_stack_pop(int_stack, &int_val);
    printf("Popped integer: %d\n", int_val);
    
    // Double stack
    DoubleStack* double_stack = double_stack_create(5);
    double_stack_push(double_stack, 3.14);
    double_stack_push(double_stack, 2.71);
    
    double double_val;
    double_stack_pop(double_stack, &double_val);
    printf("Popped double: %.2f\n", double_val);
    
    int_stack_destroy(int_stack);
    double_stack_destroy(double_stack);
    
    return 0;
}