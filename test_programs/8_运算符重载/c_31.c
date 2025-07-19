/*
8_运算符重载.md
重载~运算符实现数值取反
*/
#include <stdio.h>

typedef struct {
    int value;
} Number;

Number invert_number(Number n) {
    Number result = {~n.value};
    return result;
}

int main() {
    Number num = {5};
    Number inverted = invert_number(num);
    printf("%d\n", inverted.value);
    return 0;
}