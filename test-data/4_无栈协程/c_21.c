/*
4_无栈协程.md
async函数实现字符串连接
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concat_strings(const char* s1, const char* s2) {
    char* result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main() {
    char* result = concat_strings("Hello, ", "world!");
    printf("%s\n", result);
    free(result);
    return 0;
}