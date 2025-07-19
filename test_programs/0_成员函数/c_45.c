/*
0_成员函数.md
为struct Queue添加enqueue成员函数，入队操作
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;

void init_queue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

void enqueue(Queue* queue, int value) {
    QueueNode* new_node = (QueueNode*)malloc(sizeof(QueueNode));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    new_node->data = value;
    new_node->next = NULL;
    
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;
}

void print_queue(Queue* queue) {
    QueueNode* current = queue->front;
    printf("Queue contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("(size: %d)\n", queue->size);
}

void cleanup_queue(Queue* queue) {
    QueueNode* current = queue->front;
    while (current != NULL) {
        QueueNode* temp = current;
        current = current->next;
        free(temp);
    }
    queue->front = queue->rear = NULL;
    queue->size = 0;
}

int main() {
    Queue queue;
    init_queue(&queue);
    
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    
    print_queue(&queue);
    
    cleanup_queue(&queue);
    return 0;
}