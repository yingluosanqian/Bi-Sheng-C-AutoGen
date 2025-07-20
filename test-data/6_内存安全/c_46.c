/*
6_内存安全.md
安全区数组示例：安全的数组定义和访问
*/
#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    printf("%d\n", arr[2]);
    return 0;
}