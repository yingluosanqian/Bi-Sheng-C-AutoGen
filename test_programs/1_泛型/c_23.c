/*
1_泛型.md
常量泛型实现固定容量的队列，容量大小可配置
*/
#include <stdio.h>
#include <stdlib.h>

/* Fixed capacity queue for integers with capacity 5 */
struct IntQueue5 {
    int data[5];
    int front;
    int rear;
    int size;
};

void init_queue5(struct IntQueue5 *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

int enqueue5(struct IntQueue5 *queue, int item) {
    if (queue->size >= 5) {
        return 0; /* Queue full */
    }
    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % 5;
    queue->size++;
    return 1;
}

int dequeue5(struct IntQueue5 *queue, int *item) {
    if (queue->size == 0) {
        return 0; /* Queue empty */
    }
    *item = queue->data[queue->front];
    queue->front = (queue->front + 1) % 5;
    queue->size--;
    return 1;
}

/* Fixed capacity queue for integers with capacity 10 */
struct IntQueue10 {
    int data[10];
    int front;
    int rear;
    int size;
};

void init_queue10(struct IntQueue10 *queue) {
    queue->front = 0;
    queue->rear = 0;
    queue->size = 0;
}

int enqueue10(struct IntQueue10 *queue, int item) {
    if (queue->size >= 10) {
        return 0; /* Queue full */
    }
    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % 10;
    queue->size++;
    return 1;
}

int dequeue10(struct IntQueue10 *queue, int *item) {
    if (queue->size == 0) {
        return 0; /* Queue empty */
    }
    *item = queue->data[queue->front];
    queue->front = (queue->front + 1) % 10;
    queue->size--;
    return 1;
}

int main() {
    struct IntQueue5 queue5;
    struct IntQueue10 queue10;
    int val;
    
    init_queue5(&queue5);
    init_queue10(&queue10);
    
    /* Test queue with capacity 5 */
    enqueue5(&queue5, 1);
    enqueue5(&queue5, 2);
    enqueue5(&queue5, 3);
    
    dequeue5(&queue5, &val);
    printf("%d\n", val);
    dequeue5(&queue5, &val);
    printf("%d\n", val);
    
    /* Test queue with capacity 10 */
    enqueue10(&queue10, 4);
    enqueue10(&queue10, 5);
    
    dequeue10(&queue10, &val);
    printf("%d\n", val);
    dequeue10(&queue10, &val);
    printf("%d\n", val);
    
    return 0;
}