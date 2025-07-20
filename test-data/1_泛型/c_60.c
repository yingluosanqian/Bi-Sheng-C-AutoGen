/*
1_泛型.md
泛型结构体实现简单的图节点，支持任意类型数据
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct GraphNode {
    void *data;
    struct GraphNode **neighbors;
    int neighbor_count;
    int capacity;
};

struct GraphNode* create_node(void *data, size_t data_size) {
    struct GraphNode *node = malloc(sizeof(struct GraphNode));
    node->data = malloc(data_size);
    memcpy(node->data, data, data_size);
    node->neighbors = NULL;
    node->neighbor_count = 0;
    node->capacity = 0;
    return node;
}

void add_neighbor(struct GraphNode *node, struct GraphNode *neighbor) {
    if (node->neighbor_count >= node->capacity) {
        node->capacity = node->capacity == 0 ? 1 : node->capacity * 2;
        node->neighbors = realloc(node->neighbors, node->capacity * sizeof(struct GraphNode*));
    }
    node->neighbors[node->neighbor_count++] = neighbor;
}

void print_int_node(struct GraphNode *node) {
    printf("Node data: %d\n", *(int*)node->data);
}

void free_node(struct GraphNode *node) {
    free(node->data);
    free(node->neighbors);
    free(node);
}

int main() {
    int value1 = 42;
    int value2 = 24;
    
    struct GraphNode *node1 = create_node(&value1, sizeof(int));
    struct GraphNode *node2 = create_node(&value2, sizeof(int));
    
    add_neighbor(node1, node2);
    
    print_int_node(node1);
    print_int_node(node2);
    
    free_node(node1);
    free_node(node2);
    
    return 0;
}