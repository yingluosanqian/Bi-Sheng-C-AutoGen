/*
7_owned-struct-类型.md
创建owned struct Window实例并初始化width和height
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int width;
    int height;
} Window;

int main() {
    Window w = {.width = 800, .height = 600};
    printf("Window created: %dx%d\n", w.width, w.height);
    return 0;
}