/*
7_owned-struct-类型.md
创建owned struct Gamepad实例并初始化buttons和axes
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int buttons;
    float axes;
} Gamepad;

void print_gamepad(Gamepad *pad) {
    printf("{\"buttons\": %d, \"axes\": %.2f}", pad->buttons, pad->axes);
}

int main() {
    Gamepad pad = {.buttons = 8, .axes = 1.5f};
    print_gamepad(&pad);
    return 0;
}