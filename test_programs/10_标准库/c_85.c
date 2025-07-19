/*
10_标准库.md
使用Rc包装Vec实现共享列表
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    size_t len;
} Vec;

Vec make_vec(int val) {
    Vec v;
    v.data = malloc(sizeof(int));
    *v.data = val;
    v.len = 1;
    return v;
}

void print_vec(Vec *v) {
    printf("%d\n", *v->data);
}

int main(void) {
    Vec v = make_vec(42);
    
    // Manual sharing by copying pointer (unsafe)
    Vec v_shared = v;
    
    print_vec(&v_shared);
    
    // Must not free both - would cause double free
    free(v.data);
    return 0;
}