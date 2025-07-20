/*
10_标准库.md
使用Vec存储字符串并遍历打印
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* strings[] = {"Hello", "World", "!"};
    size_t count = sizeof(strings)/sizeof(strings[0]);
    
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", strings[i]);
    }
    
    return 0;
}