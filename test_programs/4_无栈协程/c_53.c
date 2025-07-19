/*
4_无栈协程.md
async函数处理日历事件添加
*/
#include <stdio.h>
#include <stdlib.h>

struct Event {
    char* name;
    int day;
};

typedef void (*callback)(struct Event);

void add_event_async(char* name, int day, callback cb) {
    struct Event e = {name, day};
    cb(e);
}

void handle_event(struct Event e) {
    printf("{\"event\":\"%s\",\"day\":%d}", e.name, e.day);
}

int main() {
    add_event_async("Meeting", 15, handle_event);
    return 0;
}