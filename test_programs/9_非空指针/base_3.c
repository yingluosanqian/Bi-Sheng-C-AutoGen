/*指针赋值影响原变量*/

#include <stdio.h>

int main() {
    int value = 7;
    int *ptr = NULL;
    ptr = &value;
    *ptr += 10;
    printf("{result: %d}\n", value); // 应输出17
    return 0;
}
