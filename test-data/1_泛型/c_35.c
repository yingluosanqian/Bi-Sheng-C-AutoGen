/*
1_泛型.md
泛型成员函数为队列添加enqueue操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

struct IntQueue {
    int *data;
    int front;
    int rear;
    int capacity;
};

struct FloatQueue {
    float *data;
    int front;
    int rear;
    int capacity;
};

struct IntQueue* create_int_queue(int capacity) {
    struct IntQueue *queue = malloc(sizeof(struct IntQueue));
    queue->data = malloc(sizeof(int) * capacity);
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

struct FloatQueue* create_float_queue(int capacity) {
    struct FloatQueue *queue = malloc(sizeof(struct FloatQueue));
    queue->data = malloc(sizeof(float) * capacity);
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

int enqueue_int(struct IntQueue *queue, int item) {
    if ((queue->rear + 1) % queue->capacity == queue->front) {
        return 0;
    }
    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % queue->capacity;
    return 1;
}

int enqueue_float(struct FloatQueue *queue, float item) {
    if ((queue->rear + 1) % queue->capacity == queue->front) {
        return 0;
    }
    queue->data[queue->rear] = item;
    queue->rear = (queue->rear + 1) % queue->capacity;
    return 1;
}

int main() {
    struct IntQueue *int_queue = create_int_queue(5);
    struct FloatQueue *float_queue = create_float_queue(5);
    
    enqueue_int(int_queue, 10);
    enqueue_int(int_queue, 20);
    enqueue_float(float_queue, 3.14);
    enqueue_float(float_queue, 2.71);
    
    printf("Int queue: %d %d\n", int_queue->data[0], int_queue->data[1]);
    printf("Float queue: %.2f %.2f\n", float_queue->data[0], float_queue->data[1]);
    
    free(int_queue->data);
    free(int_queue);
    free(float_queue->data);
    free(float_queue);
    
    return 0;
}