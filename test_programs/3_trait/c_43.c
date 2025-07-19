/*
3_trait.md
Vehicle trait为Car和Bike结构体实现start方法
*/
#include <stdio.h>

/* In standard C, we simulate traits using function pointers */

typedef struct {
    void (*start)(void*);
} Vehicle;

typedef struct {
    int wheels;
    Vehicle vehicle;
} Car;

typedef struct {
    int wheels;
    Vehicle vehicle;
} Bike;

void car_start(void* this) {
    Car* car = (Car*)this;
    printf("Car with %d wheels started\n", car->wheels);
}

void bike_start(void* this) {
    Bike* bike = (Bike*)this;
    printf("Bike with %d wheels started\n", bike->wheels);
}

int main() {
    Car car = {4, {car_start}};
    Bike bike = {2, {bike_start}};
    
    car.vehicle.start(&car);
    bike.vehicle.start(&bike);
    
    return 0;
}