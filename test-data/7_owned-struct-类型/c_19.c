/*
7_owned-struct-类型.md
创建owned struct Computer实例并初始化brand和model
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Computer {
    char brand[50];
    char model[50];
};

int main() {
    struct Computer my_computer;
    strcpy(my_computer.brand, "Dell");
    strcpy(my_computer.model, "XPS 15");
    
    printf("Computer: %s %s\n", my_computer.brand, my_computer.model);
    return 0;
}