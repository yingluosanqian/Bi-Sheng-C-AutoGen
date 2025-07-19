/*
4_无栈协程.md
async函数处理图像加载模拟
*/
#include <stdio.h>
#include <stdlib.h>

void load_image_callback(int id, void (*callback)(int)) {
    // Simulate async loading
    printf("{\"image_id\":%d,\"status\":\"loaded\"}", id);
    if (callback) callback(id);
}

void handle_loaded_image(int id) {
    // Image loaded handler
}

int main() {
    load_image_callback(123, handle_loaded_image);
    return 0;
}