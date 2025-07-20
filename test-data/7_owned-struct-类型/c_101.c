/*
7_owned-struct-类型.md
创建owned struct KeyEvent实例并初始化key和action
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int action;
} KeyEvent;

int main() {
    KeyEvent event = {.key = 65, .action = 1};
    printf("Key: %d, Action: %d\n", event.key, event.action);
    return 0;
}