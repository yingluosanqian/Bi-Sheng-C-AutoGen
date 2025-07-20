/*
4_无栈协程.md
async函数处理评论查询模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Comment {
    int id;
    char* text;
};

struct Comment query_comment_sync(int id) {
    // Simulate database query
    struct Comment comment;
    comment.id = id;
    comment.text = "Sample comment text";
    return comment;
}

int main() {
    // In standard C, we simulate async behavior with sync calls
    struct Comment comment = query_comment_sync(1);
    printf("{\"id\": %d, \"text\": \"%s\"}", comment.id, comment.text);
    return 0;
}