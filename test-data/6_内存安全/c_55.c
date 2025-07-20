/*
6_内存安全.md
安全区模块示例：模块间的安全接口
*/
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5, y = 10;
    swap(&x, &y);
    printf("x: %d, y: %d\n", x, y);
    return 0;
}