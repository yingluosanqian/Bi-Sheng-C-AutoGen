/*
1_泛型.md
泛型成员函数为链表添加insert操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

// Standard C implementation using void pointers

// Node structure for any type (using void pointer)
struct Node {
    void *data;
    struct Node *next;
};

// List structure
struct List {
    struct Node *head;
    size_t data_size; // Size of the data type
};

// Initialize list
void list_init(struct List *list, size_t data_size) {
    list->head = NULL;
    list->data_size = data_size;
}

// Insert at the beginning - for any type
void list_insert(struct List *list, void *data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    // Allocate memory for the data and copy it
    new_node->data = malloc(list->data_size);
    if (new_node->data == NULL) {
        free(new_node);
        printf("Memory allocation failed\n");
        return;
    }
    
    // Copy the data
    for (size_t i = 0; i < list->data_size; i++) {
        ((char*)new_node->data)[i] = ((char*)data)[i];
    }
    
    new_node->next = list->head;
    list->head = new_node;
}

// Print integer list
void print_int_list(struct List *list) {
    struct Node *current = list->head;
    printf("List contents: ");
    while (current != NULL) {
        printf("%d ", *((int *)current->data));
        current = current->next;
    }
    printf("\n");
}

// Print float list
void print_float_list(struct List *list) {
    struct Node *current = list->head;
    printf("List contents: ");
    while (current != NULL) {
        printf("%.2f ", *((float *)current->data));
        current = current->next;
    }
    printf("\n");
}

// Free list memory
void list_free(struct List *list) {
    struct Node *current = list->head;
    struct Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
    
    list->head = NULL;
}

int main() {
    // Integer list
    struct List int_list;
    list_init(&int_list, sizeof(int));
    
    int val1 = 10;
    int val2 = 20;
    int val3 = 30;
    
    list_insert(&int_list, &val1);
    list_insert(&int_list, &val2);
    list_insert(&int_list, &val3);
    
    print_int_list(&int_list);
    
    // Float list
    struct List float_list;
    list_init(&float_list, sizeof(float));
    
    float fval1 = 10.5;
    float fval2 = 20.5;
    float fval3 = 30.5;
    
    list_insert(&float_list, &fval1);
    list_insert(&float_list, &fval2);
    list_insert(&float_list, &fval3);
    
    print_float_list(&float_list);
    
    // Free memory
    list_free(&int_list);
    list_free(&float_list);
    
    return 0;
}
