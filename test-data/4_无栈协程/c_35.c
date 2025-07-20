/*
4_无栈协程.md
async函数处理长度单位转换
*/
#include <stdio.h>
#include <stdlib.h>

/* Simulating async behavior in standard C */
int convert_inches_to_cm(int inches) {
    return inches * 2.54;
}

int main() {
    int inches = 10;
    int cm = convert_inches_to_cm(inches);
    printf("{\"inches\":%d,\"centimeters\":%d}", inches, cm);
    return 0;
}