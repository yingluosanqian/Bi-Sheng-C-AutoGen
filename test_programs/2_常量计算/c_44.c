/*
2_常量计算.md
constexpr实现编译期汉诺塔步数计算
*/
#include <stdio.h>

/* Runtime calculation in standard C */
int hanoi_steps(int n) {
    if (n == 1) {
        return 1;
    }
    return 2 * hanoi_steps(n - 1) + 1;
}

int main() {
    int steps = hanoi_steps(5);
    printf("Hanoi tower with 5 disks requires %d steps\n", steps);
    return 0;
}
