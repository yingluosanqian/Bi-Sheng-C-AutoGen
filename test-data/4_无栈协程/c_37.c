/*
4_无栈协程.md
async函数处理货币转换
*/
#include <stdio.h>
#include <stdlib.h>

/* Simulated async function in standard C using callbacks */
typedef struct {
    int (*callback)(float, void*);
    void* user_data;
} AsyncContext;

void convert_currency(float amount, float rate, AsyncContext* context) {
    float result = amount * rate;
    context->callback(result, context->user_data);
}

int print_result(float result, void* unused) {
    printf("{\"amount\": %.2f}", result);
    return 0;
}

int main() {
    AsyncContext context = {
        .callback = print_result,
        .user_data = NULL
    };
    convert_currency(100.0f, 0.85f, &context);
    return 0;
}