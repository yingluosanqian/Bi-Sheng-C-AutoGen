/*
0_成员函数.md
为char类型添加print成员函数，打印字符
*/
#include <stdio.h>

// In standard C, we need to create a separate function
void print_char(const char* c) {
    printf("%c", *c);
}

int main() {
    char c = 'A';
    print_char(&c);
    return 0;
}
