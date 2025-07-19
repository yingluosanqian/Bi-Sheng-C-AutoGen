/*
1_泛型.md
泛型结构体实现二叉树节点，支持任意类型数据
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Binary tree node for integers */
struct IntTreeNode {
    int data;
    struct IntTreeNode* left;
    struct IntTreeNode* right;
};

/* Binary tree node for strings */
struct StringTreeNode {
    char* data;
    struct StringTreeNode* left;
    struct StringTreeNode* right;
};

/* Functions for integer tree */
struct IntTreeNode* create_int_node(int value) {
    struct IntTreeNode* node = (struct IntTreeNode*)malloc(sizeof(struct IntTreeNode));
    if (node) {
        node->data = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void print_int_inorder(struct IntTreeNode* node) {
    if (node != NULL) {
        print_int_inorder(node->left);
        printf("%d ", node->data);
        print_int_inorder(node->right);
    }
}

/* Functions for string tree */
struct StringTreeNode* create_string_node(const char* value) {
    struct StringTreeNode* node = (struct StringTreeNode*)malloc(sizeof(struct StringTreeNode));
    if (node) {
        node->data = (char*)malloc(strlen(value) + 1);
        strcpy(node->data, value);
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void print_string_inorder(struct StringTreeNode* node) {
    if (node != NULL) {
        print_string_inorder(node->left);
        printf("%s ", node->data);
        print_string_inorder(node->right);
    }
}

int main() {
    /* Create integer tree */
    struct IntTreeNode* int_root = create_int_node(10);
    int_root->left = create_int_node(5);
    int_root->right = create_int_node(15);
    
    printf("Integer tree: ");
    print_int_inorder(int_root);
    printf("\n");
    
    /* Create string tree */
    struct StringTreeNode* str_root = create_string_node("root");
    str_root->left = create_string_node("left");
    str_root->right = create_string_node("right");
    
    printf("String tree: ");
    print_string_inorder(str_root);
    printf("\n");
    
    return 0;
}