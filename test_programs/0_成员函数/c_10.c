/*
0_成员函数.md
为int类型添加square成员函数，计算平方值
*/
#include <stdio.h>

/* Standard C implementation using a regular function */
int square(int number) {
    return number * number;
}

int main() {
    int num = 5;
    int result = square(num);
    
    printf("{\"value\": %d, \"square\": %d}", num, result);
    
    return 0;
}