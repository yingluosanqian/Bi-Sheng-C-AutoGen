/*
6_内存安全.md
安全区游戏示例：游戏开发中的安全模式
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int* score = malloc(sizeof(int));
    *score = 0;
    
    // Game update loop
    for (int i = 0; i < 10; i = i + 1) {
        *score = *score + 10;
    }
    
    printf("Final score: %d\n", *score);
    free(score);
    score = NULL;
    return 0;
}