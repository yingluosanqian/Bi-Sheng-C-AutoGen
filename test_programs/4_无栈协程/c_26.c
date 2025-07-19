/*
4_无栈协程.md
async函数处理简单的HTTP GET请求模拟
*/
#include <stdio.h>
#include <stdlib.h>

int simulate_http_get() {
    return 200; // Simulate HTTP 200 OK response
}

int main() {
    int response = simulate_http_get();
    printf("{\"status\": %d}", response);
    return 0;
}