/*
10_标准库.md
使用safe_free释放一个结构体指针
*/
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

int main(void) {
    struct Point *p = malloc(sizeof(struct Point));
    p->x = 10;
    p->y = 20;
    free(p);
    return 0;
}