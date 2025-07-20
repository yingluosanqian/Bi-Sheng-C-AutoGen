/*
0_成员函数.md
为int类型添加digit_count成员函数，计算数字位数
*/
#include <stdio.h>
#include <stdlib.h>

int digit_count(int num) {
    int count = 0;
    if (num == 0) {
        return 1;
    }
    if (num < 0) {
        num = -num;
    }
    while (num > 0) {
        count++;
        num /= 10;
    }
    return count;
}

int main() {
    int numbers[] = {123, -456, 0, 7890};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < size; i++) {
        printf("Number %d has %d digits\n", numbers[i], digit_count(numbers[i]));
    }
    
    return 0;
}