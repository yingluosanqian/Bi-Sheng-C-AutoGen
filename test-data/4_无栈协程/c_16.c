/*
4_无栈协程.md
async函数检查数字是否为偶数
*/
#include <stdio.h>
#include <stdlib.h>

int is_even(int num) {
    return num % 2 == 0;
}

int main() {
    int number = 4;
    int result = is_even(number);
    printf("{\"number\": %d, \"is_even\": %d}", number, result);
    return 0;
}