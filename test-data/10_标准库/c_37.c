/*
10_标准库.md
使用String的slice方法获取子字符串
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
    char *str = "Hello World";
    char *substr = malloc(6);
    memcpy(substr, str + 6, 5);
    substr[5] = '\0';
    printf("%s\n", substr);
    free(substr);
    return 0;
}