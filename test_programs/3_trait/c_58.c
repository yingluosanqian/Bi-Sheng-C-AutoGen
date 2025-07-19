/*
3_trait.md
多态函数接收trait指针参数调用不同类型实现
*/
#include <stdio.h>

typedef struct {
    int (*getArea)(void*);
} Shape;

struct Square {
    int side;
};

struct Rectangle {
    int width;
    int height;
};

int Square_getArea(struct Square* this) {
    return this->side * this->side;
}

int Rectangle_getArea(struct Rectangle* this) {
    return this->width * this->height;
}

void printArea(Shape* shape, void* obj) {
    printf("%d\n", shape->getArea(obj));
}

int main() {
    struct Square sq = {5};
    struct Rectangle rect = {3, 4};
    
    Shape squareShape = {.getArea = (int(*)(void*))Square_getArea};
    Shape rectShape = {.getArea = (int(*)(void*))Rectangle_getArea};
    
    printArea(&squareShape, &sq);
    printArea(&rectShape, &rect);
    
    return 0;
}