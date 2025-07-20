/*用指针修改函数外部变量的值*/

#include <stdio.h>

void update(int *x) {
    *x = 100;
}

int main() {
    int value = 10;
    update(&value);
    printf("{result: %d}\n", value); // 应输出100
    return 0;
}
