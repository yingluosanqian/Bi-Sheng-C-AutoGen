/*
4_无栈协程.md
async函数处理传感器数据读取
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*poll)(void*);
    void (*free)(void*);
} Future;

int sensor_poll(void* unused) {
    return 42; // Simulated sensor reading
}

void sensor_free(void* unused) {}

Future* read_sensor() {
    Future* f = malloc(sizeof(Future));
    f->poll = sensor_poll;
    f->free = sensor_free;
    return f;
}

int main() {
    Future* sensor = read_sensor();
    int value = sensor->poll(NULL);
    sensor->free(NULL);
    printf("%d", value);
    return 0;
}