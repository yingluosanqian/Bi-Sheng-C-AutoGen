/*指针先赋值，再修改指向内容*/

#include <stdio.h>

int main() {
    int x = 3;
    int *p;
    p = &x;
    printf("{before: %d}\n", *p); // 应输出3
    *p = 9;
    printf("{after: %d}\n", x); // 应输出9
    return 0;
}
