/*
7_owned-struct-类型.md
定义owned struct MouseEvent，包含button和position成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int button;
    int position;
} MouseEvent;

void printMouseEvent(const MouseEvent* event) {
    printf("Button: %d, Position: %d\n", event->button, event->position);
}

int main() {
    MouseEvent event = {.button = 1, .position = 100};
    printMouseEvent(&event);
    return 0;
}