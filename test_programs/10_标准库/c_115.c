/*
10_标准库.md
使用LinkedList实现后进先出的任务栈
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push(Node** head, int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = *head;
    *head = new_node;
}

int pop(Node** head) {
    Node* temp = *head;
    int data = temp->data;
    *head = (*head)->next;
    free(temp);
    return data;
}

int main() {
    Node* stack = NULL;
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);
    
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    printf("%d\n", pop(&stack));
    
    return 0;
}