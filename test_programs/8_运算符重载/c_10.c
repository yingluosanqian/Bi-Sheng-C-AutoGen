/*
8_运算符重载.md
重载>=运算符比较两个时间戳先后
*/
#include <stdio.h>

typedef struct {
    long sec;
    long nsec;
} Timestamp;

int timestamp_ge(Timestamp a, Timestamp b) {
    if (a.sec > b.sec) return 1;
    if (a.sec < b.sec) return 0;
    return a.nsec >= b.nsec;
}

int main() {
    Timestamp t1 = {10, 0};
    Timestamp t2 = {9, 999999999};
    printf("%d\n%d\n", timestamp_ge(t1, t2), timestamp_ge(t2, t1));
    return 0;
}