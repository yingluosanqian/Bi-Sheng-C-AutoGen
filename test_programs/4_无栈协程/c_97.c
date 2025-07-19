/*
4_无栈协程.md
async函数实现简单的加密功能
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* xor_encrypt(const char* input, char key) {
    size_t len = strlen(input);
    char* output = malloc(len + 1);
    
    for (size_t i = 0; i < len; i++) {
        output[i] = input[i] ^ key;
    }
    output[len] = '\0';
    
    return output;
}

int main() {
    const char* message = "Hello";
    char key = 'K';
    
    char* encrypted = xor_encrypt(message, key);
    printf("%s", encrypted);
    
    free(encrypted);
    return 0;
}