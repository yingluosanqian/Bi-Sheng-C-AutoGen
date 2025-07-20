/*测试所有权转移 (owned 指针)*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *p1 = (int*)malloc(sizeof(int));
    if (p1 == NULL) return 1;
    *p1 = 10;

    int *p2 = p1;
    p1 = NULL; 

    *p2 = 20;
    printf("{result: %d}\n", *p2);

    free(p2);
    return 0;
}