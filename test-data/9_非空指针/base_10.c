/*函数尝试修改指针本身*/

#include <stdio.h>

void changePointer(int *p) {
    int local = 99;
    p = &local;
    *p = 77;
}

int main() {
    int x = 10;
    int *ptr = &x;
    changePointer(ptr);
    printf("{result: %d}\n", x); // 应输出10，不变
    return 0;
}
