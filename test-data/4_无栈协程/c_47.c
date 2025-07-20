/*
4_无栈协程.md
async函数实现简单的聊天消息发送
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_completed;
    char* message;
} ChatResult;

typedef ChatResult (*SendFunc)(char*);

ChatResult send_message(char* msg) {
    ChatResult result;
    result.is_completed = 1;
    result.message = msg;
    return result;
}

void chat() {
    SendFunc sender = send_message;
    ChatResult res = sender("Hello from C!");
    printf("%s\n", res.message);
}

int main() {
    chat();
    return 0;
}