/*
4_无栈协程.md
async函数处理文件读取模拟
*/
#include <stdio.h>
#include <string.h>

int read_file_sync() {
    const char* content = "hello world";
    return strlen(content);
}

int main() {
    int length = read_file_sync();
    printf("{\"length\":%d}", length);
    return 0;
}