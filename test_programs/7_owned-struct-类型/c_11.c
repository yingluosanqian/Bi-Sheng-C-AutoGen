/*
7_owned-struct-类型.md
创建owned struct Animal实例并初始化species和age
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char species[50];
    int age;
} Animal;

void print_animal(Animal *a) {
    printf("{\"species\": \"%s\", \"age\": %d}", a->species, a->age);
}

int main() {
    Animal a;
    strcpy(a.species, "Tiger");
    a.age = 5;
    
    print_animal(&a);
    return 0;
}