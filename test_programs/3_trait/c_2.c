/*
3_trait.md
定义Shape trait，为Square结构体实现getArea和getPerimeter方法
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we use function pointers to simulate polymorphism
typedef struct {
    int (*getArea)(void*);
    int (*getPerimeter)(void*);
} ShapeInterface;

typedef struct {
    int side;
    ShapeInterface* vtable;
} Square;

int Square_getArea(void* this) {
    Square* square = (Square*)this;
    return square->side * square->side;
}

int Square_getPerimeter(void* this) {
    Square* square = (Square*)this;
    return 4 * square->side;
}

ShapeInterface Square_vtable = {
    .getArea = Square_getArea,
    .getPerimeter = Square_getPerimeter
};

int main() {
    Square square = {.side = 5, .vtable = &Square_vtable};
    int area = square.vtable->getArea(&square);
    int perimeter = square.vtable->getPerimeter(&square);
    
    printf("{\"area\":%d,\"perimeter\":%d}", area, perimeter);
    return 0;
}