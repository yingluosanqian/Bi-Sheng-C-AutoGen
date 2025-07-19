/*
3_trait.md
定义Display trait，为char类型实现show方法显示字符
*/
#include <stdio.h>

/* In standard C, we use a regular function */
void show_char(char c) {
    printf("'%c'", c);
}

int main() {
    char ch = 'A';
    show_char(ch);
    return 0;
}