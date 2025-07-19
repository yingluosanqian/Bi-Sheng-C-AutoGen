/*
7_owned-struct-类型.md
定义owned struct Line，包含start和end点
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

void print_line(Line *line) {
    printf("Line from (%d, %d) to (%d, %d)\n", 
           line->start.x, line->start.y, 
           line->end.x, line->end.y);
}

int main() {
    Line line = {
        .start = {.x = 0, .y = 0},
        .end = {.x = 10, .y = 10}
    };
    
    print_line(&line);
    
    return 0;
}