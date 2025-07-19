/*
0_成员函数.md
为struct BinaryTree添加insert成员函数，插入节点
*/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct BinaryTree {
    struct TreeNode* root;
};

struct TreeNode* create_node(int data) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* insert_helper(struct TreeNode* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert_helper(root->left, data);
    } else if (data > root->data) {
        root->right = insert_helper(root->right, data);
    }
    
    return root;
}

void insert_node(struct BinaryTree* tree, int data) {
    tree->root = insert_helper(tree->root, data);
}

void inorder_helper(struct TreeNode* root) {
    if (root != NULL) {
        inorder_helper(root->left);
        printf("%d ", root->data);
        inorder_helper(root->right);
    }
}

void print_tree(struct BinaryTree* tree) {
    inorder_helper(tree->root);
    printf("\n");
}

int main() {
    struct BinaryTree tree = {NULL};
    
    insert_node(&tree, 50);
    insert_node(&tree, 30);
    insert_node(&tree, 70);
    insert_node(&tree, 20);
    insert_node(&tree, 40);
    
    print_tree(&tree);
    
    return 0;
}