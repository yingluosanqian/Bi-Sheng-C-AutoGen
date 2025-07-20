/*
6_内存安全.md
安全区地址操作限制示例：禁止取地址操作
*/
#include <stdio.h>

int main() {
    int x = 10;
    int *p = &x;  // Allowed in standard C
    printf("%d\n", *p);
    return 0;
}