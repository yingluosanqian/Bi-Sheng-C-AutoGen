/*指针指向变量变化，赋值影响不同对象*/
#include <stdio.h>

int main() {
    int a = 1, b = 2;
    int *p = &a;
    *p = 100;
    p = &b;
    *p = 200;
    printf("{result: a=%d, b=%d}\n", a, b); // 应输出 a=100, b=200
    return 0;
}
