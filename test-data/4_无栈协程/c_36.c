/*
4_无栈协程.md
async函数处理重量单位转换
*/
#include <stdio.h>
#include <stdlib.h>

// Simulating async behavior with plain functions in C
float pounds_to_kg(float pounds) {
    return pounds * 0.453592;
}

int main() {
    float pounds = 10.0;
    float kg = pounds_to_kg(pounds);
    printf("{\"pounds\":%.2f,\"kilograms\":%.2f}", pounds, kg);
    return 0;
}