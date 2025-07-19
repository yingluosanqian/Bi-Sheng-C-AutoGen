/*
7_owned-struct-类型.md
创建owned struct Temperature实例并初始化value和scale
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float value;
    char scale; // 'C' for Celsius, 'F' for Fahrenheit
} Temperature;

void print_temperature(Temperature *temp) {
    printf("Temperature: %.1f°%c\n", temp->value, temp->scale);
}

int main() {
    Temperature temp = {.value = 25.5, .scale = 'C'};
    print_temperature(&temp);
    return 0;
}