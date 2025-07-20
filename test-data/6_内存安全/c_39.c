/*
6_内存安全.md
所有权转移函数示例：函数间转移owned指针所有权
*/
#include <stdio.h>
#include <stdlib.h>

int* create_int(int value) {
    int* p = malloc(sizeof(int));
    *p = value;
    return p;
}

int* transfer_ownership(int* p) {
    return p;
}

void free_int(int* p) {
    free(p);
}

int main() {
    int* p = create_int(42);
    int* q = transfer_ownership(p);
    printf("%d\n", *q);
    free_int(q);
    return 0;
}