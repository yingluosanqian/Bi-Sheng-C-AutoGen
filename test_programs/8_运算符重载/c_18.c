/*
8_运算符重载.md
重载-运算符实现集合差集
*/
#include <stdio.h>

typedef struct {
    int data[10];
    int size;
} IntSet;

int contains(IntSet *set, int value) {
    for (int i = 0; i < set->size; i++) {
        if (set->data[i] == value) return 1;
    }
    return 0;
}

IntSet set_difference(IntSet a, IntSet b) {
    IntSet result = { .size = 0 };
    for (int i = 0; i < a.size; i++) {
        if (!contains(&b, a.data[i])) {
            result.data[result.size++] = a.data[i];
        }
    }
    return result;
}

int main() {
    IntSet a = { .data = {1, 2, 3, 4}, .size = 4 };
    IntSet b = { .data = {3, 4, 5, 6}, .size = 4 };
    
    IntSet diff = set_difference(a, b);
    
    printf("Set difference: ");
    for (int i = 0; i < diff.size; i++) {
        printf("%d ", diff.data[i]);
    }
    printf("\n");
    return 0;
}