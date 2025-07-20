/*
3_trait.md
const修饰的trait指针变量的使用
*/
#include <stdio.h>

typedef struct {
    int (*getValue)(const void*);
} Trait;

int int_getValue(const int* this) {
    return *this;
}

int main() {
    int x = 42;
    const Trait* t = &(Trait){.getValue = (int(*)(const void*))int_getValue};
    printf("%d\n", t->getValue(&x));
    return 0;
}