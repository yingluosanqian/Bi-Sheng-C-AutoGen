/*
10_标准库.md
使用String创建一个空字符串并添加字符
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *str = malloc(1);
    str[0] = '\0';
    str = realloc(str, 2);
    strcat(str, "a");
    printf("%s\n", str);
    free(str);
    return 0;
}