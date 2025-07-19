/*
10_标准库.md
使用Rc和RefCell共享访问一个计数器
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int ref_count;
} Counter;

Counter* create_counter() {
    Counter* c = malloc(sizeof(Counter));
    c->count = 0;
    c->ref_count = 1;
    return c;
}

void increment(Counter* c) {
    c->count = c->count + 1;
}

void add_ref(Counter* c) {
    c->ref_count = c->ref_count + 1;
}

void release(Counter* c) {
    c->ref_count = c->ref_count - 1;
    if (c->ref_count == 0) {
        free(c);
    }
}

int main(void) {
    Counter* counter = create_counter();
    
    // First reference
    Counter* ref1 = counter;
    add_ref(ref1);
    
    // Second reference
    Counter* ref2 = counter;
    add_ref(ref2);
    
    increment(ref1);
    increment(ref2);
    
    printf("%d\n", counter->count);
    
    release(ref1);
    release(ref2);
    release(counter);
    
    return 0;
}