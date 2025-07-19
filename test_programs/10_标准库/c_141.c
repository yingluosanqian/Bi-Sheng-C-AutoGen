/*
10_标准库.md
使用String格式化输出浮点数据为字符串
*/
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    double num = 3.14159;
    char buffer[32];
    snprintf(buffer, sizeof(buffer), "%.2f", num);
    printf("%s\n", buffer);
    return 0;
}