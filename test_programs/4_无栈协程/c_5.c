/*
4_无栈协程.md
async函数实现简单的计数器
*/
#include <stdio.h>
#include <stdlib.h>

/* Simulating async behavior in C */
typedef struct {
    int state;
    int count;
} Counter;

int counter_step(Counter* c) {
    switch(c->state) {
        case 0: c->count = 0; c->state++; break;
        case 1: c->count++; c->state++; break;
        case 2: c->count++; return 1;  // Done
    }
    return 0;  // Not done
}

int main() {
    Counter c = {0, 0};
    while(!counter_step(&c)) {}
    printf("%d\n", c.count);
    return 0;
}