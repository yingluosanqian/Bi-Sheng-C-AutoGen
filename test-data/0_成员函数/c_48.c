/*
0_成员函数.md
为struct LinkedList添加prepend成员函数，前置插入节点
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct LinkedList {
    struct Node* head;
};

void prepend_node(struct LinkedList* list, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        return;
    }
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
}

void print_list(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    struct LinkedList list = {NULL};
    
    prepend_node(&list, 3);
    prepend_node(&list, 2);
    prepend_node(&list, 1);
    
    print_list(&list);
    
    free_list(&list);
    return 0;
}