/*
10_标准库.md
使用Rc::strong_count方法查看引用计数
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int ref_count;
} RcInt;

void print_ref_count(RcInt* rc) {
    printf("%d\n", rc->ref_count);
}

int main(void) {
    RcInt* rc = malloc(sizeof(RcInt));
    rc->value = 42;
    rc->ref_count = 1;
    
    print_ref_count(rc);
    
    free(rc);
    return 0;
}