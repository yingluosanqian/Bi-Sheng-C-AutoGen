/*通过多个指针操作同一变量*/

#include <stdio.h>

int main() {
    int x = 5;
    int *p1 = &x;
    int *p2 = p1;
    *p2 = 15;
    printf("{result: %d}\n", *p1); // 应输出15
    return 0;
}
