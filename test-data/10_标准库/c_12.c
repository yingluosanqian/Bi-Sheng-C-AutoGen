/*
10_标准库.md
使用String的find方法查找字符'a'的位置
*/
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *str = "banana";
    char *pos = strchr(str, 'a');
    if (pos) {
        printf("%ld", pos - str);
    } else {
        printf("-1");
    }
    return 0;
}