/*
8_运算符重载.md
重载%运算符实现循环缓冲区
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int buffer[5];
    int head;
    int tail;
    int count;
    int capacity;
} CircularBuffer;

int positive_mod(int a, int mod) {
    int r = a % mod;
    return r < 0 ? r + mod : r;
}

void push(CircularBuffer *cb, int value) {
    if (cb->count == cb->capacity) {
        cb->head = positive_mod(cb->head + 1, cb->capacity);
    } else {
        cb->count++;
    }
    cb->buffer[cb->tail] = value;
    cb->tail = positive_mod(cb->tail + 1, cb->capacity);
}

int pop(CircularBuffer *cb) {
    int value = cb->buffer[cb->head];
    cb->head = positive_mod(cb->head + 1, cb->capacity);
    cb->count--;
    return value;
}

int main() {
    CircularBuffer cb = { .head=0, .tail=0, .count=0, .capacity=5 };
    
    push(&cb, 1);
    push(&cb, 2);
    push(&cb, 3);
    push(&cb, 4);
    push(&cb, 5);
    push(&cb, 6);  // Overwrites oldest (1)
    
    printf("%d", pop(&cb));  // Outputs 2
    return 0;
}