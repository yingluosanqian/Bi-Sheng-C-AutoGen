/*
7_owned-struct-类型.md
定义owned struct Box，包含width、height和depth
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
    int depth;
} Box;

void print_box(Box *box) {
    printf("Box dimensions: %d x %d x %d\n", box->width, box->height, box->depth);
}

int main() {
    Box box = {10, 20, 30};
    print_box(&box);
    return 0;
}