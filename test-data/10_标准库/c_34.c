/*
10_标准库.md
使用safe_malloc分配一个结构体并初始化成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

int main(void) {
    struct Point *p = (struct Point *)malloc(sizeof(struct Point));
    p->x = 10;
    p->y = 20;
    free(p);
    return 0;
}