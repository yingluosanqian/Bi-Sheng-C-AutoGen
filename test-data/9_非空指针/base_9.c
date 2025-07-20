/*交换两个变量的值*/

#include <stdio.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int main() {
    int x = 5, y = 9;
    swap(&x, &y);
    printf("{result: x=%d, y=%d}\n", x, y); // 应输出 x=9, y=5
    return 0;
}
