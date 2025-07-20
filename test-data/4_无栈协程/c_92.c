/*
4_无栈协程.md
async函数处理链表操作模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

typedef void (*callback)(int, void*);

void traverse_async(struct Node* head, callback cb, void* context) {
    while (head != NULL) {
        cb(head->data, context);
        head = head->next;
    }
}

void sum_callback(int value, void* context) {
    int* sum = (int*)context;
    *sum += value;
}

int main() {
    // Create list: 1 -> 2 -> 3
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 1;
    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;
    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    int sum = 0;
    traverse_async(head, sum_callback, &sum);
    
    printf("%d\n", sum);
    
    // Free memory
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}