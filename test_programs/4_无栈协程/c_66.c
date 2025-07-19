/*
4_无栈协程.md
async函数处理订单创建模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Order {
    int id;
    int amount;
};

struct Order create_order(int id, int amount) {
    struct Order order = {id, amount};
    printf("{\"id\":%d,\"amount\":%d}", order.id, order.amount);
    return order;
}

int main() {
    struct Order order = create_order(123, 50);
    return 0;
}