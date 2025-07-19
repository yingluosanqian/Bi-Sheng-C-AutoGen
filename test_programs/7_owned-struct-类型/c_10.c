/*
7_owned-struct-类型.md
定义owned struct Animal，包含species和age成员
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Animal {
    char species[50];
    int age;
};

void print_animal(struct Animal *animal) {
    printf("Species: %s, Age: %d\n", animal->species, animal->age);
}

int main() {
    struct Animal lion = {
        .species = "Lion",
        .age = 5
    };
    
    print_animal(&lion);
    
    return 0;
}