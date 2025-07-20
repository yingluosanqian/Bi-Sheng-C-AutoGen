/*
3_trait.md
不同trait指针变量之间的比较操作
*/
#include <stdio.h>
#include <stdlib.h>

struct A { int x; };
struct B { int y; };

int main() {
    struct A a = {1};
    struct B b = {2};
    
    void *p1 = &a;
    void *p2 = &b;
    
    if (p1 == p2) {
        printf("Pointers are equal\n");
    } else {
        printf("Pointers are not equal\n");
    }
    
    return 0;
}