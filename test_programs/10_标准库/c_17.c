/*
10_标准库.md
使用Option的Some包装一个整数
*/
#include <stdio.h>

int main() {
    int *p = NULL;
    if (1) {
        int x = 42;
        p = &x;
    }
    if (p != NULL) {
        printf("Value: %d\n", *p);
    } else {
        printf("No value\n");
    }
    return 0;
}