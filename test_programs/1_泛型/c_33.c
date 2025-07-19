/*
1_泛型.md
泛型成员函数为栈结构添加push操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Integer Stack implementation
typedef struct {
    int* data;
    int capacity;
    int top;
} IntStack;

IntStack* create_int_stack(int capacity) {
    IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->data = (int*)malloc(capacity * sizeof(int));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

int int_stack_push(IntStack* stack, int value) {
    if (stack->top >= stack->capacity - 1) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = value;
    return 1;
}

// Float Stack implementation
typedef struct {
    float* data;
    int capacity;
    int top;
} FloatStack;

FloatStack* create_float_stack(int capacity) {
    FloatStack* stack = (FloatStack*)malloc(sizeof(FloatStack));
    if (stack == NULL) {
        return NULL;
    }
    stack->data = (float*)malloc(capacity * sizeof(float));
    if (stack->data == NULL) {
        free(stack);
        return NULL;
    }
    stack->capacity = capacity;
    stack->top = -1;
    return stack;
}

int float_stack_push(FloatStack* stack, float value) {
    if (stack->top >= stack->capacity - 1) {
        return 0; // Stack overflow
    }
    stack->data[++stack->top] = value;
    return 1;
}

int main() {
    // Integer stack
    IntStack* int_stack = create_int_stack(5);
    int_stack_push(int_stack, 10);
    int_stack_push(int_stack, 20);
    
    // Float stack
    FloatStack* float_stack = create_float_stack(5);
    float_stack_push(float_stack, 3.14);
    float_stack_push(float_stack, 2.71);
    
    printf("Integer stack top: %d\n", int_stack->data[int_stack->top]);
    printf("Float stack top: %.2f\n", float_stack->data[float_stack->top]);
    
    // Clean up
    free(int_stack->data);
    free(int_stack);
    free(float_stack->data);
    free(float_stack);
    
    return 0;
}
