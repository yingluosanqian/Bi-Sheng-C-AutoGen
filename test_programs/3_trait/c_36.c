/*
3_trait.md
trait方法中使用This指针访问结构体成员
*/
#include <stdio.h>

struct Square {
    int side;
};

int square_area(struct Square* this) {
    return this->side * this->side;
}

int main() {
    struct Square s = {5};
    printf("%d\n", square_area(&s));
    return 0;
}