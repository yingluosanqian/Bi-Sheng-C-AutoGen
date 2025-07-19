/*
4_无栈协程.md
async函数处理日历事件查询
*/
#include <stdio.h>
#include <stdlib.h>

struct Event {
    char* name;
    int day;
};

struct Event get_event_sync() {
    struct Event e = {"Team Meeting", 15};
    return e;
}

int main() {
    struct Event e = get_event_sync();
    printf("{\"name\": \"%s\", \"day\": %d}", e.name, e.day);
    return 0;
}