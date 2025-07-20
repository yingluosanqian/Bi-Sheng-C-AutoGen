/*
4_无栈协程.md
async函数实现简单的堆栈处理
*/
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 10

struct Stack {
    int data[STACK_SIZE];
    int top;
};

void push(struct Stack *s, int value) {
    s->data[s->top++] = value;
}

int pop(struct Stack *s) {
    return s->data[--s->top];
}

int main() {
    struct Stack s = { .top = 0 };
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    int result = pop(&s);
    result = pop(&s);
    result = pop(&s);
    printf("%d\n", result);
    return 0;
}