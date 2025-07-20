/*
10_标准库.md
使用LinkedList的front方法访问头元素
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int main(void) {
    Node* head = malloc(sizeof(Node));
    head->data = 42;
    head->next = NULL;
    
    printf("%d\n", head->data);
    
    free(head);
    return 0;
}