/*
1_泛型.md
泛型成员函数为链表添加delete操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

// Standard C implementation requires separate linked list implementations for each data type

// Integer linked list
typedef struct IntNode {
    int data;
    struct IntNode* next;
} IntNode;

typedef struct IntLinkedList {
    IntNode* head;
} IntLinkedList;

// Initialize integer linked list
void int_list_init(IntLinkedList* list) {
    list->head = NULL;
}

// Add integer to list
void int_list_add(IntLinkedList* list, int value) {
    IntNode* newNode = (IntNode*)malloc(sizeof(IntNode));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
}

// Delete integer node with specific value
int int_list_delete(IntLinkedList* list, int value) {
    IntNode* current = list->head;
    IntNode* prev = NULL;
    
    // If head contains the value
    if (current != NULL && current->data == value) {
        list->head = current->next;
        free(current);
        return 1; // Successfully deleted
    }
    
    // Search for the value
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    // If value wasn't found
    if (current == NULL) {
        return 0; // Value not found
    }
    
    // Unlink the node and free it
    prev->next = current->next;
    free(current);
    return 1; // Successfully deleted
}

// Print integer list
void int_list_print(IntLinkedList* list) {
    IntNode* current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Float linked list
typedef struct FloatNode {
    float data;
    struct FloatNode* next;
} FloatNode;

typedef struct FloatLinkedList {
    FloatNode* head;
} FloatLinkedList;

// Initialize float linked list
void float_list_init(FloatLinkedList* list) {
    list->head = NULL;
}

// Add float to list
void float_list_add(FloatLinkedList* list, float value) {
    FloatNode* newNode = (FloatNode*)malloc(sizeof(FloatNode));
    newNode->data = value;
    newNode->next = list->head;
    list->head = newNode;
}

// Delete float node with specific value
int float_list_delete(FloatLinkedList* list, float value) {
    FloatNode* current = list->head;
    FloatNode* prev = NULL;
    
    // If head contains the value
    if (current != NULL && current->data == value) {
        list->head = current->next;
        free(current);
        return 1; // Successfully deleted
    }
    
    // Search for the value
    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }
    
    // If value wasn't found
    if (current == NULL) {
        return 0; // Value not found
    }
    
    // Unlink the node and free it
    prev->next = current->next;
    free(current);
    return 1; // Successfully deleted
}

// Print float list
void float_list_print(FloatLinkedList* list) {
    FloatNode* current = list->head;
    printf("List: ");
    while (current != NULL) {
        printf("%.1f ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    // Test integer list
    IntLinkedList intList;
    int_list_init(&intList);
    int_list_add(&intList, 10);
    int_list_add(&intList, 20);
    int_list_add(&intList, 30);
    
    printf("Integer ");
    int_list_print(&intList);
    
    int_list_delete(&intList, 20);
    printf("After deleting 20: ");
    int_list_print(&intList);
    
    // Test float list
    FloatLinkedList floatList;
    float_list_init(&floatList);
    float_list_add(&floatList, 1.1);
    float_list_add(&floatList, 2.2);
    float_list_add(&floatList, 3.3);
    
    printf("Float ");
    float_list_print(&floatList);
    
    float_list_delete(&floatList, 2.2);
    printf("After deleting 2.2: ");
    float_list_print(&floatList);
    
    return 0;
}