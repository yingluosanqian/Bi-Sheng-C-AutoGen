/*
0_成员函数.md
为int类型添加count_bits成员函数，统计二进制1的个数
*/
#include <stdio.h>
#include <stdint.h>

/* Standard C requires a standalone function */
int count_bits(int num) {
    int count = 0;
    while (num) {
        count += num & 1;
        num >>= 1;
    }
    return count;
}

int main() {
    int number = 0b1101; // Binary 1101 (decimal 13)
    printf("Number of set bits: %d\n", count_bits(number));
    return 0;
}
