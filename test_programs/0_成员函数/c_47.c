/*
0_成员函数.md
为struct LinkedList添加append成员函数，追加节点
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
    struct Node* tail;
};

void append_node(struct LinkedList* list, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (list->head == NULL) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
}

void print_list(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct LinkedList list = {NULL, NULL};
    
    append_node(&list, 1);
    append_node(&list, 2);
    append_node(&list, 3);
    
    print_list(&list);
    
    return 0;
}