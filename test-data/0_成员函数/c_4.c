/*
0_成员函数.md
为int类型添加abs成员函数，返回绝对值
*/
#include <stdio.h>
#include <stdlib.h>

int int_abs(int value) {
    return value < 0 ? -value : value;
}

int main() {
    int a = -42;
    int b = 25;
    int c = 0;
    
    printf("%d\n", int_abs(a));
    printf("%d\n", int_abs(b));
    printf("%d\n", int_abs(c));
    
    return 0;
}