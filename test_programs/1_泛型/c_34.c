/*
1_泛型.md
泛型成员函数为栈结构添加pop操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

struct IntStack {
    int *data;
    int top;
    int capacity;
};

struct FloatStack {
    float *data;
    int top;
    int capacity;
};

struct IntStack* create_int_stack(int capacity) {
    struct IntStack *stack = malloc(sizeof(struct IntStack));
    stack->data = malloc(sizeof(int) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

struct FloatStack* create_float_stack(int capacity) {
    struct FloatStack *stack = malloc(sizeof(struct FloatStack));
    stack->data = malloc(sizeof(float) * capacity);
    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}

void push_int(struct IntStack *stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

void push_float(struct FloatStack *stack, float value) {
    if (stack->top < stack->capacity - 1) {
        stack->data[++stack->top] = value;
    }
}

int pop_int(struct IntStack *stack, int *value) {
    if (stack->top >= 0) {
        *value = stack->data[stack->top--];
        return 1;
    }
    return 0;
}

int pop_float(struct FloatStack *stack, float *value) {
    if (stack->top >= 0) {
        *value = stack->data[stack->top--];
        return 1;
    }
    return 0;
}

int main() {
    struct IntStack *int_stack = create_int_stack(10);
    struct FloatStack *float_stack = create_float_stack(10);
    
    push_int(int_stack, 42);
    push_int(int_stack, 100);
    push_float(float_stack, 3.14);
    push_float(float_stack, 2.71);
    
    int int_val;
    float float_val;
    
    if (pop_int(int_stack, &int_val)) {
        printf("%d\n", int_val);
    }
    if (pop_float(float_stack, &float_val)) {
        printf("%.2f\n", float_val);
    }
    
    free(int_stack->data);
    free(int_stack);
    free(float_stack->data);
    free(float_stack);
    
    return 0;
}