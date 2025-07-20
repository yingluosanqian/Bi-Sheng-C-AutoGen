/*
4_无栈协程.md
async函数实现简单的待办事项添加
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* item;
    int completed;
} TodoItem;

TodoItem* add_todo(const char* description) {
    TodoItem* item = malloc(sizeof(TodoItem));
    item->item = strdup(description);
    item->completed = 0;
    return item;
}

void print_todo_json(TodoItem* item) {
    printf("{\"description\": \"%s\", \"completed\": %d}", item->item, item->completed);
}

int main() {
    TodoItem* item = add_todo("Buy groceries");
    print_todo_json(item);
    free(item->item);
    free(item);
    return 0;
}