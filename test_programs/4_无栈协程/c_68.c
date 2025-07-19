/*
4_无栈协程.md
async函数处理订单取消模拟
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int can_cancel_order(int order_id) {
    srand(time(NULL));
    return rand() % 2; // Randomly returns 0 or 1
}

int main() {
    int order_id = 12345;
    int result = can_cancel_order(order_id);
    printf("{\"order_id\": %d, \"can_cancel\": %d}", order_id, result);
    return 0;
}