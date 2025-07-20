/*
4_无栈协程.md
async函数实现简单的解密功能
*/
#include <stdio.h>
#include <string.h>

void decrypt(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = (str[i] - 'a' - 1 + 26) % 26 + 'a';
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = (str[i] - 'A' - 1 + 26) % 26 + 'A';
        }
    }
}

int main() {
    char message[] = "Ifmmp Xpsme";
    decrypt(message);
    printf("%s", message);
    return 0;
}