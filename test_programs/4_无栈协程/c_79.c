/*
4_无栈协程.md
async函数实现简单的消息通知
*/
#include <stdio.h>
#include <stdlib.h>

void notify_callback(int value, void (*callback)(int)) {
    printf("%d\n", value);
    callback(value);
}

void handle_notification(int value) {
    /* Notification handled */
}

int main() {
    notify_callback(42, handle_notification);
    return 0;
}