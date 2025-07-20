/*
0_成员函数.md
为int类型添加is_odd成员函数，判断是否为奇数
*/
#include <stdio.h>
#include <stdlib.h>

int is_odd(int value) {
    return value % 2 != 0;
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < size; i++) {
        if (is_odd(numbers[i])) {
            printf("%d is odd\n", numbers[i]);
        } else {
            printf("%d is even\n", numbers[i]);
        }
    }
    
    return 0;
}