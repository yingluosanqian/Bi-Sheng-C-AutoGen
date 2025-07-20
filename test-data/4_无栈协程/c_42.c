/*
4_无栈协程.md
async函数实现简单的待办事项查询
*/
#include <stdio.h>
#include <stdlib.h>

struct Todo {
    int id;
    char* title;
};

struct Todo todos[] = {
    {1, "Buy groceries"},
    {2, "Finish project"}
};

struct Todo* get_todo_sync(int id) {
    for (int i = 0; i < 2; i++) {
        if (todos[i].id == id) {
            return &todos[i];
        }
    }
    return NULL;
}

int main() {
    struct Todo* item1 = get_todo_sync(1);
    struct Todo* item2 = get_todo_sync(2);
    
    printf("{\"todos\":[{\"id\":%d,\"title\":\"%s\"},{\"id\":%d,\"title\":\"%s\"}]}",
           item1->id, item1->title, item2->id, item2->title);
    return 0;
}