/*
10_标准库.md
使用LinkedList的contains方法检查元素是否存在
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

int list_contains(struct Node* head, int value) {
    while (head != NULL) {
        if (head->data == value) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

int main() {
    struct Node* head = malloc(sizeof(struct Node));
    head->data = 1;
    head->next = malloc(sizeof(struct Node));
    head->next->data = 2;
    head->next->next = NULL;

    printf("Contains 2: %d\n", list_contains(head, 2));
    printf("Contains 3: %d\n", list_contains(head, 3));

    free(head->next);
    free(head);
    return 0;
}