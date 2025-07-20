/*
0_成员函数.md
为struct LinkedList添加remove成员函数，删除节点
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

void init_list(struct LinkedList* list) {
    list->head = NULL;
}

void add_node(struct LinkedList* list, int data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
}

int remove_node(struct LinkedList* list, int data) {
    struct Node* current = list->head;
    struct Node* prev = NULL;
    
    while (current != NULL) {
        if (current->data == data) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void print_list(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void cleanup_list(struct LinkedList* list) {
    struct Node* current = list->head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

int main() {
    struct LinkedList list;
    init_list(&list);
    
    add_node(&list, 10);
    add_node(&list, 20);
    add_node(&list, 30);
    
    printf("Original list: ");
    print_list(&list);
    
    remove_node(&list, 20);
    printf("After removing 20: ");
    print_list(&list);
    
    cleanup_list(&list);
    return 0;
}