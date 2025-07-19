/*
7_owned-struct-类型.md
定义owned struct Window，包含width和height成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
} Window;

void print_window(const Window* w) {
    printf("Window: %dx%d\n", w->width, w->height);
}

int main() {
    Window w = {800, 600};
    print_window(&w);
    return 0;
}