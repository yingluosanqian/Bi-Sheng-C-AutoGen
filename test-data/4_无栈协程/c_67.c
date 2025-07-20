/*
4_无栈协程.md
async函数处理订单查询模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Order {
    int id;
    char status[20];
};

struct Order query_order(int id) {
    struct Order order;
    order.id = id;
    sprintf(order.status, "completed");
    return order;
}

int main() {
    struct Order order = query_order(123);
    printf("{\"id\":%d,\"status\":\"%s\"}", order.id, order.status);
    return 0;
}