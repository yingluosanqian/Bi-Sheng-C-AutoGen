/*
6_内存安全.md
函数参数借用示例：函数接受借用指针参数
*/
#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 1, y = 2;
    swap(&x, &y);
    printf("x: %d, y: %d\n", x, y);
    return 0;
}