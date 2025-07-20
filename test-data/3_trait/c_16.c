/*
3_trait.md
使用trait指针变量调用不同类型的相同方法
*/
#include <stdio.h>

struct Square { int side; };
struct Circle { int radius; };

// In C, we use function pointers to simulate polymorphism
int square_area(struct Square* s) { return s->side * s->side; }
int circle_area(struct Circle* c) { return 3 * c->radius * c->radius; }

typedef struct {
    int (*area)(void*);
} Shape;

void print_area(Shape* shape, void* obj) {
    printf("%d\n", shape->area(obj));
}

int main() {
    struct Square sq = {5};
    struct Circle ci = {3};
    
    Shape square_shape = {.area = (int(*)(void*))square_area};
    Shape circle_shape = {.area = (int(*)(void*))circle_area};
    
    print_area(&square_shape, &sq);
    print_area(&circle_shape, &ci);
    
    return 0;
}