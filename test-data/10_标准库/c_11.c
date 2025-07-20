/*
10_标准库.md
使用String的at方法获取字符串的第三个字符
*/
#include <stdio.h>

int main(void) {
    char str[] = "hello";
    printf("%c\n", str[2]); // Unsafe direct access
    return 0;
}