/*
3_trait.md
trait方法返回值为结构体成员的计算结果
*/
#include <stdio.h>

struct Square {
    int side;
};

int square_get_area(struct Square* this) {
    return this->side * this->side;
}

int main() {
    struct Square s = {5};
    int area = square_get_area(&s);
    printf("%d", area);
    return 0;
}