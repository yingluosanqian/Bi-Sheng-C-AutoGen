/*
10_标准库.md
使用Vec实现循环缓冲区功能
*/
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int main() {
    int *buffer = malloc(BUFFER_SIZE * sizeof(int));
    int head = 0;
    int tail = 0;
    
    // Push 3 items
    buffer[tail] = 1;
    tail = (tail + 1) % BUFFER_SIZE;
    buffer[tail] = 2;
    tail = (tail + 1) % BUFFER_SIZE;
    buffer[tail] = 3;
    tail = (tail + 1) % BUFFER_SIZE;
    
    // Pop 2 items
    printf("%d\n", buffer[head]);
    head = (head + 1) % BUFFER_SIZE;
    printf("%d\n", buffer[head]);
    head = (head + 1) % BUFFER_SIZE;
    
    free(buffer);
    return 0;
}