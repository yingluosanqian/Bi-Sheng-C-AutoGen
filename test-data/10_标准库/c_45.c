/*
10_标准库.md
使用Scheduler并行处理多个IO任务
*/
#include <stdio.h>
#include <pthread.h>

void* task(void* arg) {
    int id = *(int*)arg;
    printf("Task %d completed\n", id);
    return NULL;
}

int main() {
    pthread_t threads[2];
    int ids[2] = {1, 2};
    
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, task, &ids[i]);
    }
    
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}