/*
7_owned-struct-类型.md
定义owned struct Time，包含hour和minute成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int hour;
    int minute;
} Time;

void print_time(Time *t) {
    printf("Time: %02d:%02d\n", t->hour, t->minute);
}

int main() {
    Time t = {.hour = 14, .minute = 30};
    print_time(&t);
    return 0;
}