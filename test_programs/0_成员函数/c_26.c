/*
0_成员函数.md
为struct TreeNode添加depth成员函数，计算树深度
*/
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

int tree_depth(struct TreeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int left_depth = tree_depth(node->left);
    int right_depth = tree_depth(node->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

int main() {
    // Create a simple tree
    //      1
    //     / \
    //    2   3
    //   /
    //  4
    struct TreeNode node4 = {4, NULL, NULL};
    struct TreeNode node2 = {2, &node4, NULL};
    struct TreeNode node3 = {3, NULL, NULL};
    struct TreeNode root = {1, &node2, &node3};

    int depth = tree_depth(&root);
    printf("Tree depth: %d\n", depth);
    return 0;
}
