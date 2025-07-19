/*
0_成员函数.md
为struct BinaryTree添加search成员函数，搜索节点
*/
#include <stdio.h>
#include <stdlib.h>

struct BinaryTree {
    int data;
    struct BinaryTree* left;
    struct BinaryTree* right;
};

struct BinaryTree* search_node(struct BinaryTree* tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    
    if (tree->data == value) {
        return tree;
    }
    
    struct BinaryTree* left_result = search_node(tree->left, value);
    if (left_result != NULL) {
        return left_result;
    }
    
    return search_node(tree->right, value);
}

struct BinaryTree* create_node(int value) {
    struct BinaryTree* node = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    node->data = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    struct BinaryTree* root = create_node(10);
    root->left = create_node(5);
    root->right = create_node(15);
    root->left->left = create_node(3);
    root->left->right = create_node(7);
    
    struct BinaryTree* result = search_node(root, 7);
    if (result != NULL) {
        printf("Found: %d\n", result->data);
    } else {
        printf("Not found\n");
    }
    
    result = search_node(root, 20);
    if (result != NULL) {
        printf("Found: %d\n", result->data);
    } else {
        printf("Not found\n");
    }
    
    return 0;
}