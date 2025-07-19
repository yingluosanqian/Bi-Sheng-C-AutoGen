/*
7_owned-struct-类型.md
创建owned struct Person实例并初始化name和age
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char name[50];
    int age;
};

void print_person(struct Person *p) {
    printf("Name: %s\nAge: %d\n", p->name, p->age);
}

int main() {
    struct Person person;
    strcpy(person.name, "John Doe");
    person.age = 30;
    
    print_person(&person);
    
    return 0;
}