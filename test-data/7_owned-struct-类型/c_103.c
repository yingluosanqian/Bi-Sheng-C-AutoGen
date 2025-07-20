/*
7_owned-struct-类型.md
创建owned struct MouseEvent实例并初始化button和position
*/
#include <stdio.h>
#include <stdlib.h>

struct MouseEvent {
    int button;
    int position[2];
};

void printMouseEvent(struct MouseEvent *event) {
    printf("{\"button\":%d,\"position\":[%d,%d]}", 
           event->button, event->position[0], event->position[1]);
}

int main() {
    struct MouseEvent event = {
        .button = 1,
        .position = {100, 200}
    };
    
    printMouseEvent(&event);
    return 0;
}