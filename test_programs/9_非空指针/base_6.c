/*const int *ptr —— 指向常量的指针*/

#include <stdio.h>

int main() {
    int a = 10, b = 20;
    const int *ptr = &a;
    // *ptr = 15; // ❌ 错误：不能修改 *ptr 指向的值
    ptr = &b;      // ✅ 可以修改指针本身
    printf("{result: %d}\n", *ptr); // 应输出20
    return 0;
}
