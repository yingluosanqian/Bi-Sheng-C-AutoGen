/*
7_owned-struct-类型.md
定义owned struct KeyEvent，包含key和action成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    char action[20];
} KeyEvent;

void print_key_event(const KeyEvent *event) {
    printf("Key: %d, Action: %s\n", event->key, event->action);
}

int main() {
    KeyEvent event = {.key = 65, .action = "KEY_PRESS"};
    print_key_event(&event);
    return 0;
}