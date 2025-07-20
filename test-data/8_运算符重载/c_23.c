/*
8_运算符重载.md
重载+运算符实现时间增量
*/
#include <stdio.h>

struct Time {
    int minutes;
    int seconds;
};

struct Time addTime(struct Time t1, struct Time t2) {
    struct Time total;
    total.minutes = t1.minutes + t2.minutes;
    total.seconds = t1.seconds + t2.seconds;
    
    if (total.seconds >= 60) {
        total.minutes += total.seconds / 60;
        total.seconds %= 60;
    }
    return total;
}

int main() {
    struct Time morning = {2, 45};  // 2 min 45 sec
    struct Time evening = {1, 20};  // 1 min 20 sec
    struct Time total = addTime(morning, evening);
    
    printf("%d minutes and %d seconds\n", total.minutes, total.seconds);
    return 0;
}