/*
4_无栈协程.md
async函数实现简单的计算器
*/
#include <stdio.h>
#include <stdlib.h>

// Standard C doesn't have async/await, so we simulate with normal functions
int delay(int ms) {
    // Simulate delay (no actual async in standard C)
    return ms;
}

int add(int a, int b) {
    delay(100); // Simulate async delay
    return a + b;
}

int main() {
    int result = add(3, 4);
    printf("%d\n", result);
    return 0;
}