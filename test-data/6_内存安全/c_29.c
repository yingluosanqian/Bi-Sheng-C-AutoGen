/*
6_内存安全.md
所有权与借用结合示例：在safe区内使用owned和borrow
*/
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 1, b = 2;
    swap(&a, &b);
    printf("a: %d, b: %d\n", a, b);
    return 0;
}