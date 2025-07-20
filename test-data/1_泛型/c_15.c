/*
1_泛型.md
泛型结构体实现链表节点，支持任意类型数据
*/
#include <stdio.h>
#include <stdlib.h>

struct IntNode {
    int data;
    struct IntNode* next;
};

struct FloatNode {
    float data;
    struct FloatNode* next;
};

struct IntNode* create_int_node(int value) {
    struct IntNode* node = (struct IntNode*)malloc(sizeof(struct IntNode));
    node->data = value;
    node->next = NULL;
    return node;
}

struct FloatNode* create_float_node(float value) {
    struct FloatNode* node = (struct FloatNode*)malloc(sizeof(struct FloatNode));
    node->data = value;
    node->next = NULL;
    return node;
}

void print_int_list(struct IntNode* head) {
    struct IntNode* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void print_float_list(struct FloatNode* head) {
    struct FloatNode* current = head;
    while (current != NULL) {
        printf("%.1f ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_int_list(struct IntNode* head) {
    struct IntNode* current = head;
    while (current != NULL) {
        struct IntNode* temp = current;
        current = current->next;
        free(temp);
    }
}

void free_float_list(struct FloatNode* head) {
    struct FloatNode* current = head;
    while (current != NULL) {
        struct FloatNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct IntNode* int_head = create_int_node(10);
    int_head->next = create_int_node(20);
    int_head->next->next = create_int_node(30);
    
    struct FloatNode* float_head = create_float_node(1.5);
    float_head->next = create_float_node(2.5);
    float_head->next->next = create_float_node(3.5);
    
    print_int_list(int_head);
    print_float_list(float_head);
    
    free_int_list(int_head);
    free_float_list(float_head);
    
    return 0;
}