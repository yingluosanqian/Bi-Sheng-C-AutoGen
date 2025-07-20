/*
10_标准库.md
使用Option实现链式加法直到遇到None
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct OptionInt {
    int value;
    _Bool is_some;
} OptionInt;

OptionInt some(int value) {
    OptionInt opt = { .value = value, .is_some = 1 };
    return opt;
}

OptionInt none() {
    OptionInt opt = { .value = 0, .is_some = 0 };
    return opt;
}

int chain_add(OptionInt a, OptionInt b, OptionInt c) {
    int sum = 0;
    if (a.is_some) sum += a.value;
    if (b.is_some) sum += b.value;
    if (c.is_some) sum += c.value;
    return sum;
}

int main(void) {
    OptionInt a = some(1);
    OptionInt b = none();
    OptionInt c = some(3);
    
    int result = chain_add(a, b, c);
    printf("%d\n", result);
    return 0;
}