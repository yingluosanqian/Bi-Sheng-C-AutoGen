/*
7_owned-struct-类型.md
定义owned struct Computer，包含brand和model成员
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Computer {
    char brand[50];
    char model[50];
};

void print_computer(struct Computer *comp) {
    printf("Brand: %s\nModel: %s\n", comp->brand, comp->model);
}

int main() {
    struct Computer my_comp;
    strcpy(my_comp.brand, "Dell");
    strcpy(my_comp.model, "XPS 15");
    
    print_computer(&my_comp);
    
    return 0;
}