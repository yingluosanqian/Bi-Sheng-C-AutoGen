/*
10_标准库.md
使用Vec实现动态增长的缓冲区
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* buffer = malloc(2 * sizeof(int));
    buffer[0] = 10;
    buffer[1] = 20;
    
    int* new_buffer = realloc(buffer, 4 * sizeof(int));
    if (new_buffer) {
        buffer = new_buffer;
        buffer[2] = 30;
        buffer[3] = 40;
    }
    
    printf("%d %d %d %d\n", buffer[0], buffer[1], buffer[2], buffer[3]);
    free(buffer);
    return 0;
}