/*
4_无栈协程.md
async函数实现简单的队列处理
*/
#include <stdio.h>
#include <stdlib.h>

struct Queue {
    int items[10];
    int front;
    int rear;
};

void enqueue(struct Queue* q, int value) {
    q->items[q->rear++] = value;
}

int dequeue(struct Queue* q) {
    return q->items[q->front++];
}

int is_empty(struct Queue* q) {
    return q->front == q->rear;
}

int process_item(int item) {
    return item * 2;
}

void process_queue(struct Queue* q) {
    while (!is_empty(q)) {
        int item = dequeue(q);
        int result = process_item(item);
        printf("%d\n", result);
    }
}

int main() {
    struct Queue q = {{0}, 0, 0};
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    process_queue(&q);
    return 0;
}