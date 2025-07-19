/*
4_无栈协程.md
async函数计算数字的立方
*/
#include <stdio.h>
#include <stdlib.h>

int cube(int num) {
    return num * num * num;
}

int main() {
    int number = 3;
    int result = cube(number);
    printf("{\"result\": %d}", result);
    return 0;
}