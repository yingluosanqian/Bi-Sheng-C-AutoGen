/*
7_owned-struct-类型.md
5. Create owned struct 'Car' with model and year fields
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
    struct Car my_car = {"Tesla Model 3", 2022};
    print_car(&my_car);
    return 0;
}