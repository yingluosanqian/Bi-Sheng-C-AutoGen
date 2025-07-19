/*
3_trait.md
泛型trait Parser解析int和float字符串
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int (*parseInt)(const char*);
    float (*parseFloat)(const char*);
} Parser;

int parseInt(const char* str) {
    return atoi(str);
}

float parseFloat(const char* str) {
    return atof(str);
}

int main() {
    Parser parser = {
        .parseInt = parseInt,
        .parseFloat = parseFloat
    };
    
    const char* intStr = "123";
    const char* floatStr = "45.67";
    
    int intVal = parser.parseInt(intStr);
    float floatVal = parser.parseFloat(floatStr);
    
    printf("Parsed int: %d\n", intVal);
    printf("Parsed float: %.2f\n", floatVal);
    
    return 0;
}
