/*
8_运算符重载.md
重载>运算符比较两个温度值高低
*/
#include <stdio.h>

typedef struct {
    double celsius;
} Temperature;

int is_greater(Temperature t1, Temperature t2) {
    return t1.celsius > t2.celsius;
}

int main() {
    Temperature t1 = {25.5};
    Temperature t2 = {30.0};
    int result = is_greater(t1, t2);
    printf("%d", result);
    return 0;
}