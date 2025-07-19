/*
4_无栈协程.md
async函数实现简单的邮件发送
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int send_email(const char* to, const char* subject, const char* body) {
    printf("{\"to\":\"%s\", \"subject\":\"%s\", \"body\":\"%s\"}", to, subject, body);
    return 1;
}

int main() {
    send_email("user@example.com", "Hello", "This is a test email");
    return 0;
}