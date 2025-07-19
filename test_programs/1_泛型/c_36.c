/*
1_泛型.md
泛型成员函数为队列添加dequeue操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

/* Integer Queue */
struct IntQueue {
    int *data;
    int front;
    int rear;
    int capacity;
    int size;
};

struct IntQueue* create_int_queue(int capacity) {
    struct IntQueue *queue = malloc(sizeof(struct IntQueue));
    queue->data = malloc(sizeof(int) * capacity);
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

void enqueue_int(struct IntQueue *queue, int item) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = item;
        queue->size++;
    }
}

int dequeue_int(struct IntQueue *queue, int *item) {
    if (queue->size > 0) {
        *item = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return 1;
    }
    return 0;
}

/* Float Queue */
struct FloatQueue {
    float *data;
    int front;
    int rear;
    int capacity;
    int size;
};

struct FloatQueue* create_float_queue(int capacity) {
    struct FloatQueue *queue = malloc(sizeof(struct FloatQueue));
    queue->data = malloc(sizeof(float) * capacity);
    queue->front = 0;
    queue->rear = -1;
    queue->capacity = capacity;
    queue->size = 0;
    return queue;
}

void enqueue_float(struct FloatQueue *queue, float item) {
    if (queue->size < queue->capacity) {
        queue->rear = (queue->rear + 1) % queue->capacity;
        queue->data[queue->rear] = item;
        queue->size++;
    }
}

int dequeue_float(struct FloatQueue *queue, float *item) {
    if (queue->size > 0) {
        *item = queue->data[queue->front];
        queue->front = (queue->front + 1) % queue->capacity;
        queue->size--;
        return 1;
    }
    return 0;
}

int main() {
    struct IntQueue *int_queue = create_int_queue(5);
    struct FloatQueue *float_queue = create_float_queue(5);
    
    enqueue_int(int_queue, 10);
    enqueue_int(int_queue, 20);
    enqueue_float(float_queue, 3.14);
    enqueue_float(float_queue, 2.71);
    
    int int_val;
    float float_val;
    
    if (dequeue_int(int_queue, &int_val)) {
        printf("%d\n", int_val);
    }
    if (dequeue_int(int_queue, &int_val)) {
        printf("%d\n", int_val);
    }
    if (dequeue_float(float_queue, &float_val)) {
        printf("%.2f\n", float_val);
    }
    if (dequeue_float(float_queue, &float_val)) {
        printf("%.2f\n", float_val);
    }
    
    free(int_queue->data);
    free(int_queue);
    free(float_queue->data);
    free(float_queue);
    
    return 0;
}
