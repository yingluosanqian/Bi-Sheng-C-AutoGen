/*
0_成员函数.md
为int类型添加is_prime成员函数，判断是否为质数
*/
#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int numbers[] = {2, 3, 4, 17, 25, 29};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < count; i++) {
        int num = numbers[i];
        if (is_prime(num)) {
            printf("%d is prime\n", num);
        } else {
            printf("%d is not prime\n", num);
        }
    }
    
    return 0;
}