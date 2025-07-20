/*
8_运算符重载.md
重载*运算符实现迭代器解引用
*/
#include <stdio.h>

typedef struct {
    int *current;
} IntIterator;

int deref_iterator(IntIterator *it) {
    return *(it->current);
}

int main() {
    int data = 10;
    IntIterator it = { &data };
    printf("%d", deref_iterator(&it));
    return 0;
}