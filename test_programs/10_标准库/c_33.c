/*
10_标准库.md
使用Scheduler的run方法执行所有任务
*/
#include <stdio.h>
#include "scheduler.h"

void task(void) {
    printf("Task executed\n");
}

int main(void) {
    Scheduler_init(1);
    Scheduler_spawn(task);
    Scheduler_run();
    Scheduler_destroy();
    return 0;
}