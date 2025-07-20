/*
4_无栈协程.md
async函数实现简单的待办事项删除
*/
#include <stdio.h>
#include <stdlib.h>

struct TodoItem {
    int id;
    char* task;
};

void delete_todo(struct TodoItem* todos, int* count, int id) {
    for (int i = 0; i < *count; i++) {
        if (todos[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                todos[j] = todos[j + 1];
            }
            (*count)--;
            return;
        }
    }
}

int main() {
    struct TodoItem todos[3] = {
        {1, "Buy groceries"},
        {2, "Do laundry"},
        {3, "Clean room"}
    };
    int count = 3;
    
    delete_todo(todos, &count, 2);
    
    printf("{\"remaining_todos\": %d}", count);
    return 0;
}