/*
4_无栈协程.md
async函数实现简单的日志记录
*/
#include <stdio.h>
#include <stdlib.h>

void log_message(const char* msg) {
    printf("%s\n", msg);
}

int main() {
    log_message("This is a log message");
    return 0;
}