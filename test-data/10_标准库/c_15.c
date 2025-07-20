/*
10_标准库.md
使用LinkedList的pop_back方法移除链表尾部元素
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void push_back(Node** head, int data) {
    Node* new_node = create_node(data);
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

int pop_back(Node** head) {
    if (*head == NULL) {
        return -1; // Error
    }
    if ((*head)->next == NULL) {
        int data = (*head)->data;
        free(*head);
        *head = NULL;
        return data;
    }
    Node* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    int data = current->next->data;
    free(current->next);
    current->next = NULL;
    return data;
}

int main() {
    Node* head = NULL;
    push_back(&head, 1);
    push_back(&head, 2);
    push_back(&head, 3);
    
    printf("%d\n", pop_back(&head));
    printf("%d\n", pop_back(&head));
    
    if (head != NULL) {
        free(head);
    }
    return 0;
}