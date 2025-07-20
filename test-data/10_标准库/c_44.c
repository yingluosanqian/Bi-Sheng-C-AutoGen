/*
10_标准库.md
使用RefCell实现一个可变的缓存
*/
#include <stdio.h>
#include <stdlib.h>

struct Cache {
    int value;
};

int main(void) {
    struct Cache* cache = malloc(sizeof(struct Cache));
    cache->value = 42;
    
    // Direct mutable access in C
    cache->value = 100;
    printf("%d\n", cache->value);
    
    free(cache);
    return 0;
}