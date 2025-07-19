/*
4_无栈协程.md
async函数实现简单的计时器
*/
#include <stdio.h>
#include <unistd.h>

int main() {
    sleep(1);
    printf("1");
    return 0;
}