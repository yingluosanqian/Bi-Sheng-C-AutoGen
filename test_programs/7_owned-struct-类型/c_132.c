/*
7_owned-struct-类型.md
定义owned struct AI，包含behavior和state成员
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AI {
    char behavior[50];
    int state;
};

int main() {
    struct AI my_ai = {"learning", 1};
    
    printf("AI Behavior: %s\n", my_ai.behavior);
    printf("AI State: %d\n", my_ai.state);
    
    return 0;
}