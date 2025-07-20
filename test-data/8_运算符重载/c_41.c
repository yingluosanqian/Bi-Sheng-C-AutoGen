/*
8_运算符重载.md
重载!=运算符检查两个传感器读数
*/
#include <stdio.h>

struct SensorReading {
    int id;
    float value;
};

int areNotEqual(struct SensorReading a, struct SensorReading b) {
    return a.id != b.id || a.value != b.value;
}

int main() {
    struct SensorReading r1 = {1, 25.5};
    struct SensorReading r2 = {2, 30.0};
    int result = areNotEqual(r1, r2);
    printf("%d", result);
    return 0;
}