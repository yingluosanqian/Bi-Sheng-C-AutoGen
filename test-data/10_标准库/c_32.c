/*
10_标准库.md
使用Scheduler的spawn方法创建异步任务
*/
#include <stdio.h>
#include <pthread.h>

void* task(void* arg) {
    printf("Hello from task\n");
    return NULL;
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, task, NULL);
    pthread_join(thread, NULL);
    return 0;
}