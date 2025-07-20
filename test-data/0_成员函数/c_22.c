/*
0_成员函数.md
为int类型添加gcd静态成员函数，计算最大公约数
*/
#include <stdio.h>

// In standard C, we need to use a global function to calculate GCD
int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    int num1 = 48;
    int num2 = 18;
    
    int result = gcd(num1, num2);
    
    printf("GCD of %d and %d is %d\n", num1, num2, result);
    
    return 0;
}