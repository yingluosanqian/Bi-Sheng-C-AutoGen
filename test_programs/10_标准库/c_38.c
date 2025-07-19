/*
10_标准库.md
使用LinkedList的split_off方法分割链表
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    size_t len;
};

void push_back(struct LinkedList* list, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
    } else {
        struct Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    list->len++;
}

struct LinkedList split_off(struct LinkedList* list, size_t index) {
    struct LinkedList new_list = {NULL, 0};
    if (index == 0) {
        new_list.head = list->head;
        new_list.len = list->len;
        list->head = NULL;
        list->len = 0;
        return new_list;
    }
    
    struct Node* current = list->head;
    for (size_t i = 0; i < index - 1; i++) {
        current = current->next;
    }
    
    new_list.head = current->next;
    new_list.len = list->len - index;
    current->next = NULL;
    list->len = index;
    
    return new_list;
}

int main() {
    struct LinkedList list = {NULL, 0};
    push_back(&list, 1);
    push_back(&list, 2);
    push_back(&list, 3);
    
    struct LinkedList new_list = split_off(&list, 1);
    
    printf("Original list length: %zu\n", list.len);
    printf("New list length: %zu\n", new_list.len);
    
    return 0;
}