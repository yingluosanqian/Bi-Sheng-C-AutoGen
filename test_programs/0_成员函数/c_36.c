/*
0_成员函数.md
为int类型添加reverse成员函数，反转数字
*/
#include <stdio.h>
#include <stdlib.h>

int reverse_int(int num) {
    int reversed = 0;
    int is_negative = 0;
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num > 0) {
        reversed = reversed * 10 + num % 10;
        num /= 10;
    }
    
    return is_negative ? -reversed : reversed;
}

int main() {
    int num1 = 12345;
    int num2 = -6789;
    int num3 = 100;
    
    printf("Original: %d, Reversed: %d\n", num1, reverse_int(num1));
    printf("Original: %d, Reversed: %d\n", num2, reverse_int(num2));
    printf("Original: %d, Reversed: %d\n", num3, reverse_int(num3));
    
    return 0;
}