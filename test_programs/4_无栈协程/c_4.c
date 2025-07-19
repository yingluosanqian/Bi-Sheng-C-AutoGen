/*
4_无栈协程.md
async函数比较两个字符串是否相等
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_compare(const char *a, const char *b) {
    return strcmp(a, b) == 0;
}

int main() {
    const char *str1 = "hello";
    const char *str2 = "world";
    int result = string_compare(str1, str2);
    printf("%d", result);
    return 0;
}