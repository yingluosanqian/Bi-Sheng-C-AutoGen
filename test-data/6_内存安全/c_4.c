/*
6_内存安全.md
所有权函数参数示例：函数接受并返回owned指针
*/
#include <stdio.h>
#include <stdlib.h>

int* create_int(int value) {
    int* ptr = malloc(sizeof(int));
    *ptr = value;
    return ptr;
}

int* process_int(int* ptr) {
    *ptr += 1;
    return ptr;
}

int main() {
    int* num = create_int(42);
    num = process_int(num);
    printf("%d\n", *num);
    free(num);
    return 0;
}