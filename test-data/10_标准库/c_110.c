/*
10_标准库.md
使用String的append_char方法添加单个字符
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *str = malloc(2);
    str[0] = 'a';
    str[1] = '\0';
    
    str = realloc(str, strlen(str) + 2);
    str[1] = 'b';
    str[2] = '\0';
    
    printf("%s", str);
    free(str);
    return 0;
}