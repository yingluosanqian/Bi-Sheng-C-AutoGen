/*
0_成员函数.md
为struct BinaryTree添加height成员函数，计算树高度
*/
#include <stdio.h>
#include <stdlib.h>

struct BinaryTree {
    int data;
    struct BinaryTree* left;
    struct BinaryTree* right;
};

int calculate_height(struct BinaryTree* tree) {
    if (tree == NULL) {
        return 0;
    }
    
    int left_height = calculate_height(tree->left);
    int right_height = calculate_height(tree->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

struct BinaryTree* create_node(int data) {
    struct BinaryTree* node = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int main() {
    struct BinaryTree* root = create_node(1);
    root->left = create_node(2);
    root->right = create_node(3);
    root->left->left = create_node(4);
    root->left->right = create_node(5);
    
    int height = calculate_height(root);
    printf("%d\n", height);
    
    return 0;
}