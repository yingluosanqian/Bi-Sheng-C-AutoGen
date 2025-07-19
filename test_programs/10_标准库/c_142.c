/*
10_标准库.md
使用String构造JSON格式的字符串输出
*/
#include <stdio.h>
#include <string.h>

int main(void) {
    char json[100];
    strcpy(json, "{\"name\":\"Alice\",\"age\":25}");
    printf("%s\n", json);
    return 0;
}