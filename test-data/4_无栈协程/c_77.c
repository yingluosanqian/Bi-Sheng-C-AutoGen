/*
4_无栈协程.md
async函数处理好友删除模拟
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_completed;
    int result;
} PollResult;

typedef PollResult (*async_func)(void);

PollResult delete_friend_async(void) {
    PollResult res;
    res.is_completed = 1;
    res.result = 1; // 1 means success
    return res;
}

PollResult friend_deletion_simulator(void) {
    PollResult deletion = delete_friend_async();
    return deletion;
}

int main() {
    PollResult result = friend_deletion_simulator();
    printf("{\"success\":%d}", result.result);
    return 0;
}