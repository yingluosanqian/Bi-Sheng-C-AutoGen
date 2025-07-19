/*
3_trait.md
volatile修饰的trait指针变量的使用
*/
#include <stdio.h>

struct Square {
    int side;
};

int calculate_area(struct Square* shape) {
    return shape->side * shape->side;
}

int main() {
    struct Square s = {5};
    struct Square* volatile shape = &s;
    printf("%d", calculate_area(shape));
    return 0;
}