/*
3_trait.md
trait方法接收额外参数进行计算
*/
#include <stdio.h>

typedef struct {
    int value;
} Number;

typedef int (*Operation)(void*, int);

int add(void* this, int x) {
    Number* num = (Number*)this;
    return num->value + x;
}

int main() {
    Number num = {5};
    Operation op = add;
    int result = op(&num, 3);
    printf("%d\n", result);
    return 0;
}