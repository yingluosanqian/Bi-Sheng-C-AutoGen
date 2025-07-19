/*
4_无栈协程.md
async函数实现字符查找
*/
#include <stdio.h>
#include <string.h>

int find_char(const char *str, char target) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    const char *text = "hello world";
    char target = 'o';
    int result = find_char(text, target);
    printf("%d", result);
    return 0;
}