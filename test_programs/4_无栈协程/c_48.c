/*
4_无栈协程.md
async函数实现简单的聊天消息接收
*/
#include <stdio.h>
#include <stdlib.h>

struct Message {
    char* content;
};

struct Message receive_message() {
    struct Message msg;
    msg.content = "Hello from C";
    return msg;
}

int main() {
    struct Message msg = receive_message();
    printf("{\"message\": \"%s\"}", msg.content);
    return 0;
}