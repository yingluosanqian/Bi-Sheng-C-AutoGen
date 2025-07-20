/*const 作为函数参数 —— 只读参数*/

#include <stdio.h>

void print_value(const int *p) {
    // *p = 100; // ❌ 错误：不允许修改
    printf("{value in function: %d}\n", *p);
}

int main() {
    int x = 88;
    print_value(&x); // 应输出88
    return 0;
}
