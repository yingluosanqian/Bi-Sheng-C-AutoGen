/*
10_标准库.md
使用safe_swap交换两个整数的值和所有权
*/
#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 5;
    int y = 10;
    swap(&x, &y);
    return 0;
}