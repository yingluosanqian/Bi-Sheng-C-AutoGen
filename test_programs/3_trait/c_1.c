/*
3_trait.md
为struct Point实现Drawable trait，提供draw方法
*/
#include <stdio.h>

struct Point {
    int x;
    int y;
};

void draw_point(struct Point* this) {
    printf("Drawing point at (%d, %d)\n", this->x, this->y);
}

struct Drawable {
    void (*draw)(void*);
};

void make_drawable_point(struct Point* p, struct Drawable* drawable) {
    drawable->draw = (void (*)(void*))draw_point;
}

void test() {
    struct Point p = {10, 20};
    struct Drawable d;
    
    make_drawable_point(&p, &d);
    d.draw(&p);
}

int main() {
    test();
    return 0;
}
