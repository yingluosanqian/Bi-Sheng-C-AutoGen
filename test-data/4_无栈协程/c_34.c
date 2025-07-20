/*
4_无栈协程.md
async函数处理温度转换
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*callback)(int);
} Future;

int convert_temp(int celsius) {
    return celsius * 9 / 5 + 32;
}

void async_convert(Future* future, int celsius) {
    int result = convert_temp(celsius);
    future->callback(result);
}

int callback_handler(int result) {
    printf("{\"celsius\":25,\"fahrenheit\":%d}", result);
    return 0;
}

int main() {
    Future future = {.callback = callback_handler};
    async_convert(&future, 25);
    return 0;
}