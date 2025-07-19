/*
4_无栈协程.md
async函数读取字符串长度
*/
#include <stdio.h>
#include <string.h>

int string_length(const char *str) {
    return strlen(str);
}

int main() {
    const char *text = "Hello";
    int length = string_length(text);
    printf("{\"length\":%d}", length);
    return 0;
}