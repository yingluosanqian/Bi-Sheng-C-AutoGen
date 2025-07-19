/*
10_标准库.md
使用LinkedList的size方法获取链表长度
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

size_t list_length(struct Node* head) {
    size_t count = 0;
    struct Node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int main(void) {
    struct Node* head = NULL;
    
    // Manually creating a list with 3 nodes
    head = malloc(sizeof(struct Node));
    head->data = 1;
    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;
    head->next->next = malloc(sizeof(struct Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;
    
    size_t len = list_length(head);
    printf("%zu\n", len);
    
    // Manual cleanup - no ownership tracking
    while (head != NULL) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}