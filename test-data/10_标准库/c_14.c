/*
10_标准库.md
使用LinkedList的push_front方法在链表头部插入元素
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void push_front(Node** head, int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = *head;
    *head = new_node;
}

int main() {
    Node* head = NULL;
    push_front(&head, 42);
    printf("%d\n", head->data);
    free(head);
    return 0;
}