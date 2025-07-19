/*
8_运算符重载.md
重载|运算符实现选项合并
*/
#include <stdio.h>

struct Options {
    unsigned int value;
};

struct Options combine_options(struct Options a, struct Options b) {
    struct Options result;
    result.value = a.value | b.value;
    return result;
}

int main() {
    struct Options read = {1};
    struct Options write = {2};
    
    struct Options rw = combine_options(read, write);
    printf("%u\n", rw.value);
    
    return 0;
}