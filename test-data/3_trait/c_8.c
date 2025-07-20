/*
3_trait.md
定义Movable trait，为Car结构体实现move方法
*/
#include <stdio.h>

struct Car {
    int position;
};

void Car_move(struct Car* this, int distance) {
    this->position += distance;
    printf("Car moved to position: %d\n", this->position);
}

int main() {
    struct Car my_car = {0};
    Car_move(&my_car, 10);
    return 0;
}