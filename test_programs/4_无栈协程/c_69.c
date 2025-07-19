/*
4_无栈协程.md
async函数实现简单的支付处理
*/
#include <stdio.h>
#include <stdlib.h>

int process_payment_sync(int amount) {
    return amount * 100; // Convert to cents
}

int main() {
    int payment = process_payment_sync(10);
    printf("{\"amount_cents\": %d}", payment);
    return 0;
}