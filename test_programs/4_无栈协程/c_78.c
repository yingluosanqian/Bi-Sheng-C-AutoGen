/*
4_无栈协程.md
async函数处理好友列表查询
*/
#include <stdio.h>
#include <stdlib.h>

/* Simulating async behavior in standard C */
int query_friends() {
    /* In real C, we'd need to implement async behavior manually */
    return 3; /* Simulated friend count */
}

int main() {
    int friend_count = query_friends();
    printf("{\"friend_count\": %d}", friend_count);
    return 0;
}