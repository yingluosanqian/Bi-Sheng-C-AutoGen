/*
6_内存安全.md
借用成员访问示例：通过借用指针访问结构体成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

int main() {
    Point p = {10, 20};
    Point *ptr = &p;
    
    printf("Coordinates: (%d, %d)\n", ptr->x, ptr->y);
    
    return 0;
}