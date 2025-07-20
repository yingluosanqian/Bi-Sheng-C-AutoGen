/*
4_无栈协程.md
async函数实现字符串复制
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Simulating async behavior in standard C */
char* copy_string_sync(const char* src) {
    char* dest = malloc(strlen(src) + 1);
    strcpy(dest, src);
    return dest;
}

int main() {
    const char* original = "Hello, World!";
    char* copied = copy_string_sync(original);
    printf("%s\n", copied);
    free(copied);
    return 0;
}