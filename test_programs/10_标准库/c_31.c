/*
10_标准库.md
使用Scheduler初始化4个线程的调度器
*/
#include <stdio.h>
#include <pthread.h>

void* thread_func(void* arg) {
    return NULL;
}

int main() {
    pthread_t threads[4];
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, NULL);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}