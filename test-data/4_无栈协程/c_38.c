/*
4_无栈协程.md
async函数实现简单的游戏得分计算
*/
#include <stdio.h>
#include <stdlib.h>

int calculate_score1() {
    return 100;
}

int calculate_score2() {
    return 200;
}

int main() {
    int score1 = calculate_score1();
    int score2 = calculate_score2();
    int total = score1 + score2;
    printf("{\"total_score\": %d}", total);
    return 0;
}