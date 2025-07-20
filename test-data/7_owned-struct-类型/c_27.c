/*
7_owned-struct-类型.md
创建owned struct Time实例并初始化hour和minute
*/
#include <stdio.h>
#include <stdlib.h>

struct Time {
    int hour;
    int minute;
};

int main() {
    struct Time t = {.hour = 10, .minute = 30};
    printf("Time: %02d:%02d\n", t.hour, t.minute);
    return 0;
}