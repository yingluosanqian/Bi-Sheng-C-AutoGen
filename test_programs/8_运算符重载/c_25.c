/*
8_运算符重载.md
重载==运算符比较两个颜色值
*/
#include <stdio.h>

struct Color {
    int r;
    int g;
    int b;
};

int color_equal(struct Color c1, struct Color c2) {
    return (c1.r == c2.r) && (c1.g == c2.g) && (c1.b == c2.b);
}

int main() {
    struct Color c1 = {255, 0, 0};
    struct Color c2 = {255, 0, 0};
    printf("%d", color_equal(c1, c2));
    return 0;
}