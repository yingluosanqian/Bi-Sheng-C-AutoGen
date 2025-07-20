/*
10_标准库.md
使用Weak的upgrade方法尝试升级为Rc
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

int main() {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = 42;
    node->next = NULL;
    
    // In C, we might create a weak reference manually
    Node** weak_ref = &node;
    
    if (*weak_ref != NULL) {
        printf("Value: %d\n", (*weak_ref)->value);
    } else {
        printf("Reference expired\n");
    }
    
    free(node);
    return 0;
}