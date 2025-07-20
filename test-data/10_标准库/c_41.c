/*
10_标准库.md
使用Rc和RefCell实现可变的共享计数器
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
} Counter;

Counter* create_counter() {
    Counter* c = malloc(sizeof(Counter));
    c->count = 0;
    return c;
}

void increment(Counter* c) {
    c->count++;
}

int main() {
    Counter* counter = create_counter();
    increment(counter);
    printf("%d\n", counter->count);
    free(counter);
    return 0;
}