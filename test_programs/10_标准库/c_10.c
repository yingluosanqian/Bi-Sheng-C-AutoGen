/*
10_标准库.md
使用String的length方法获取字符串长度
*/
#include <stdio.h>
#include <string.h>

int main(void) {
    char *str = "hello";
    size_t len = strlen(str);
    printf("%zu", len);
    return 0;
}