/*
7_owned-struct-类型.md
定义owned struct Temperature，包含value和scale成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float value;
    char scale;
} Temperature;

void print_temperature(const Temperature *temp) {
    if (temp->scale == 'C') {
        printf("Temperature: %.2f°C\n", temp->value);
    } else {
        printf("Temperature: %.2f°F\n", temp->value);
    }
}

int main() {
    Temperature temp = {25.5f, 'C'};
    print_temperature(&temp);
    
    Temperature temp2 = {78.9f, 'F'};
    print_temperature(&temp2);
    
    return 0;
}