/*
8_运算符重载.md
重载|运算符实现位标志合并
*/
#include <stdio.h>

typedef struct {
    int value;
} Flags;

Flags combine_flags(Flags a, Flags b) {
    Flags result = {a.value | b.value};
    return result;
}

int main() {
    Flags read = {1};      // 0001
    Flags write = {2};     // 0010
    Flags rw = combine_flags(read, write);
    printf("%d\n", rw.value);  // Output: 3 (0011)
    return 0;
}