/*
6_内存安全.md
安全区内使用泛型函数交换两个整数值
*/
#include <stdio.h>
#include <stdlib.h>

void swap(void *a, void *b, size_t size) {
    char *temp = malloc(size);
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
    free(temp);
}

int main() {
    int a = 1, b = 2;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b, sizeof(int));
    printf("After swap: a=%d, b=%d\n", a, b);
    return 0;
}