/*
10_标准库.md
使用forget函数忘记一个整数指针的所有权
*/
#include <stdlib.h>

int main(void) {
    int *p = malloc(sizeof(int));
    *p = 42;
    /* No forget equivalent - must manually manage */
    return 0;
}