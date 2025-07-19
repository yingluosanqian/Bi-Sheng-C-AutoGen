/*
7_owned-struct-类型.md
创建owned struct Line实例并初始化起点终点
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

int main() {
    Line line = {
        .start = {.x = 1, .y = 2},
        .end = {.x = 3, .y = 4}
    };
    
    printf("Start: (%d, %d)\n", line.start.x, line.start.y);
    printf("End: (%d, %d)\n", line.end.x, line.end.y);
    
    return 0;
}