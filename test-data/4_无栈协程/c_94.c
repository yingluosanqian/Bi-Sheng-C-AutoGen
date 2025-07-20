/*
4_无栈协程.md
async函数实现简单的图算法
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 4

int graph[MAX_NODES][MAX_NODES] = {
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0}
};

int visited[MAX_NODES] = {0};
int result[MAX_NODES];
int result_index = 0;

void bfs(int start) {
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    
    visited[start] = 1;
    queue[rear++] = start;
    
    while (front < rear) {
        int current = queue[front++];
        result[result_index++] = current;
        
        for (int i = 0; i < MAX_NODES; i++) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main() {
    bfs(0);
    
    printf("[ ");
    for (int i = 0; i < MAX_NODES; i++) {
        printf("%d ", result[i]);
    }
    printf("]\n");
    
    return 0;
}