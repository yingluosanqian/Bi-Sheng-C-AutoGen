/*
2_常量计算.md
使用constexpr判断一个数是否是奇数
*/
#include <stdio.h>
#include <stdbool.h>

// In standard C, we can't use constexpr, so we use a macro
#define IS_ODD(n) ((n) % 2 != 0)

int main() {
    int num = 7;
    
    if (IS_ODD(num)) {
        printf("%d is odd\n", num);
    } else {
        printf("%d is even\n", num);
    }
    
    return 0;
}
