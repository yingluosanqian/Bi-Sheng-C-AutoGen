/*
4_无栈协程.md
async函数处理系统设置保存
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int (*save)(void*);
    void* data;
} SettingsOperation;

int save_settings(void* data) {
    printf("Settings saved\n");
    return 1;
}

int main() {
    SettingsOperation op = {.save = save_settings, .data = NULL};
    int result = op.save(op.data);
    return 0;
}