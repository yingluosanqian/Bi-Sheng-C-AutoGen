/*
1_泛型.md
泛型成员函数为二叉树添加insert操作，支持任意类型
*/
#include <stdio.h>
#include <stdlib.h>

// Binary tree node for integers
struct IntTreeNode {
    int data;
    struct IntTreeNode* left;
    struct IntTreeNode* right;
};

// Binary tree for integers
struct IntBinaryTree {
    struct IntTreeNode* root;
};

// Binary tree node for floats
struct FloatTreeNode {
    float data;
    struct FloatTreeNode* left;
    struct FloatTreeNode* right;
};

// Binary tree for floats
struct FloatBinaryTree {
    struct FloatTreeNode* root;
};

// Insert function for integer tree
void int_tree_insert(struct IntBinaryTree* tree, int value) {
    struct IntTreeNode* new_node = (struct IntTreeNode*)malloc(sizeof(struct IntTreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    
    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }
    
    struct IntTreeNode* current = tree->root;
    while (1) {
        if (value < current->data) {
            if (current->left == NULL) {
                current->left = new_node;
                break;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = new_node;
                break;
            }
            current = current->right;
        }
    }
}

// Insert function for float tree
void float_tree_insert(struct FloatBinaryTree* tree, float value) {
    struct FloatTreeNode* new_node = (struct FloatTreeNode*)malloc(sizeof(struct FloatTreeNode));
    new_node->data = value;
    new_node->left = NULL;
    new_node->right = NULL;
    
    if (tree->root == NULL) {
        tree->root = new_node;
        return;
    }
    
    struct FloatTreeNode* current = tree->root;
    while (1) {
        if (value < current->data) {
            if (current->left == NULL) {
                current->left = new_node;
                break;
            }
            current = current->left;
        } else {
            if (current->right == NULL) {
                current->right = new_node;
                break;
            }
            current = current->right;
        }
    }
}

// In-order traversal for integer tree
void int_inorder_traversal(struct IntTreeNode* node) {
    if (node != NULL) {
        int_inorder_traversal(node->left);
        printf("%d ", node->data);
        int_inorder_traversal(node->right);
    }
}

// In-order traversal for float tree
void float_inorder_traversal(struct FloatTreeNode* node) {
    if (node != NULL) {
        float_inorder_traversal(node->left);
        printf("%.1f ", node->data);
        float_inorder_traversal(node->right);
    }
}

int main() {
    // Integer tree
    struct IntBinaryTree int_tree = {NULL};
    int_tree_insert(&int_tree, 5);
    int_tree_insert(&int_tree, 3);
    int_tree_insert(&int_tree, 7);
    int_tree_insert(&int_tree, 1);
    int_tree_insert(&int_tree, 9);
    
    printf("Integer tree: ");
    int_inorder_traversal(int_tree.root);
    printf("\n");
    
    // Float tree
    struct FloatBinaryTree float_tree = {NULL};
    float_tree_insert(&float_tree, 5.5);
    float_tree_insert(&float_tree, 3.2);
    float_tree_insert(&float_tree, 7.8);
    float_tree_insert(&float_tree, 1.1);
    float_tree_insert(&float_tree, 9.9);
    
    printf("Float tree: ");
    float_inorder_traversal(float_tree.root);
    printf("\n");
    
    return 0;
}