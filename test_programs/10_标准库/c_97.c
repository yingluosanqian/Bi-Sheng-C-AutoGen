/*
10_标准库.md
使用String解析命令行参数为键值对
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: %s <key> <value>\n", argv[0]);
        return 1;
    }
    
    char* key = strdup(argv[1]);
    char* value = strdup(argv[2]);
    
    printf("%s=%s\n", key, value);
    
    free(key);
    free(value);
    return 0;
}