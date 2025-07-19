/*
2_常量计算.md
使用constexpr实现编译时查找表生成
*/
#include <stdio.h>

int square(int n) {
    return n * n;
}

int main() {
    int i;
    for (i = 0; i < 5; i++) {
        printf("%d\n", square(i));
    }
    return 0;
}