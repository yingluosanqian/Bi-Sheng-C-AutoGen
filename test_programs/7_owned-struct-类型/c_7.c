/*
7_owned-struct-类型.md
创建owned struct Car实例并初始化model和year
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Car {
    char model[50];
    int year;
};

int main() {
    struct Car my_car;
    strcpy(my_car.model, "Tesla Model S");
    my_car.year = 2022;
    
    printf("Car: %s, Year: %d\n", my_car.model, my_car.year);
    return 0;
}