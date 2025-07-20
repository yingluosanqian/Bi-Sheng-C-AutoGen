/*
8_运算符重载.md
重载<运算符比较两个矩形面积大小
*/
#include <stdio.h>

typedef struct {
    int width;
    int height;
} Rectangle;

int compare_area(Rectangle a, Rectangle b) {
    return (a.width * a.height) < (b.width * b.height);
}

int main() {
    Rectangle rect1 = {3, 4};  // Area 12
    Rectangle rect2 = {2, 5};  // Area 10
    printf("%d\n", compare_area(rect1, rect2));
    return 0;
}