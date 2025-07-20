/*
6_内存安全.md
安全区泛型约束示例：对泛型参数的安全约束
*/
#include <stdio.h>

void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

int main() {
    int a = 1, b = 2;
    swap(&a, &b, sizeof(int));
    printf("a: %d, b: %d\n", a, b);
    return 0;
}