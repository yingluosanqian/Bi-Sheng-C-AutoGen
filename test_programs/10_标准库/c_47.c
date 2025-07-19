/*
10_标准库.md
使用Vec实现栈数据结构
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *stack = malloc(10 * sizeof(int));
    int top = -1;
    
    stack[++top] = 42;  // Push
    int val = stack[top--];  // Pop
    
    free(stack);
    return 0;
}