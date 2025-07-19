/*
6_内存安全.md
安全区泛型示例：safe泛型函数实现类型安全操作
*/
#include <stdio.h>
#include <stdlib.h>

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int main() {
    int a = 1, b = 2;
    printf("Before swap: a=%d, b=%d\n", a, b);
    swap(&a, &b, sizeof(int));
    printf("After swap: a=%d, b=%d\n", a, b);
    
    double x = 1.5, y = 2.5;
    printf("Before swap: x=%.1f, y=%.1f\n", x, y);
    swap(&x, &y, sizeof(double));
    printf("After swap: x=%.1f, y=%.1f\n", x, y);
    
    return 0;
}