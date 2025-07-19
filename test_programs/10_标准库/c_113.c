/*
10_标准库.md
使用LinkedList的back方法访问尾元素
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_list(int value) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = value;
    head->next = NULL;
    return head;
}

void push_back(Node* head, int value) {
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (Node*)malloc(sizeof(Node));
    current->next->data = value;
    current->next->next = NULL;
}

int back(Node* head) {
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    return current->data;
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    Node* list = create_list(42);
    push_back(list, 99);
    printf("%d\n", back(list));
    free_list(list);
    return 0;
}