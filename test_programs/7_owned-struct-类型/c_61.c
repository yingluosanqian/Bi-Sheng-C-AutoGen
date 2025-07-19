/*
7_owned-struct-类型.md
创建owned struct Box实例并初始化width、height和depth
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int depth;
} Box;

void print_box(Box *box) {
    printf("Box dimensions: %dx%dx%d\n", box->width, box->height, box->depth);
}

int main() {
    Box box = {10, 20, 30};
    print_box(&box);
    return 0;
}