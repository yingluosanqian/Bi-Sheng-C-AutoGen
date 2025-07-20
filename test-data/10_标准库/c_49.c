/*
10_标准库.md
使用LinkedList实现队列数据结构
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void enqueue(Queue* q, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue* q) {
    if (q->front == NULL) return -1;
    
    Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) q->rear = NULL;
    
    free(temp);
    return value;
}

int main() {
    Queue q = {NULL, NULL};
    
    enqueue(&q, 10);
    enqueue(&q, 20);
    
    printf("%d\n", dequeue(&q));
    printf("%d\n", dequeue(&q));
    
    return 0;
}