/*
4_无栈协程.md
async函数等待多个子任务完成
*/
#include <stdio.h>
#include <pthread.h>

int task1() {
    return 10;
}

int task2() {
    return 20;
}

void* thread_wrapper1(void* arg) {
    int* result = (int*)arg;
    *result = task1();
    return NULL;
}

void* thread_wrapper2(void* arg) {
    int* result = (int*)arg;
    *result = task2();
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int result1, result2;
    
    pthread_create(&t1, NULL, thread_wrapper1, &result1);
    pthread_create(&t2, NULL, thread_wrapper2, &result2);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("%d\n", result1 + result2);
    return 0;
}