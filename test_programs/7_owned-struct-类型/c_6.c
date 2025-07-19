/*
7_owned-struct-类型.md
定义owned struct Car，包含model和year成员
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char model[50];
    int year;
};

void print_car(struct Car *car) {
    printf("Model: %s\nYear: %d\n", car->model, car->year);
}

int main() {
    struct Car my_car;
    strcpy(my_car.model, "Tesla Model 3");
    my_car.year = 2020;
    
    print_car(&my_car);
    
    return 0;
}