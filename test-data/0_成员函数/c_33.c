/*
0_成员函数.md
为struct String添加length成员函数，计算字符串长度
*/
#include <stdio.h>
#include <string.h>

struct String {
    char data[100];
};

int string_length(struct String* str) {
    return strlen(str->data);
}

int main() {
    struct String str;
    strcpy(str.data, "Hello, World!");
    
    int len = string_length(&str);
    printf("%d\n", len);
    
    return 0;
}