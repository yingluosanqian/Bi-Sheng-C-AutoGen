/*
4_无栈协程.md
async函数实现简单的权限检查
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*poll)(void*);
    void (*free)(void*);
    int is_allowed;
} Future;

int poll_permission(void* this) {
    Future* f = (Future*)this;
    f->is_allowed = 1;  // Simulate permission granted
    return f->is_allowed;
}

void free_permission(void* this) {
    free(this);
}

Future* check_permission() {
    Future* f = malloc(sizeof(Future));
    f->poll = poll_permission;
    f->free = free_permission;
    f->is_allowed = 0;
    return f;
}

int main() {
    Future* permission = check_permission();
    permission->poll(permission);
    printf("{\"allowed\": %d}", permission->is_allowed);
    permission->free(permission);
    return 0;
}