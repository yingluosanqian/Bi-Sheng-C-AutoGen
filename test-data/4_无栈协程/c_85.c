/*
4_无栈协程.md
async函数处理系统更新安装
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we simulate async behavior with callbacks
void download_update(int time, void (*callback)(int)) {
    // Simulate download taking 'time' milliseconds
    callback(time);
}

void install_update(int time) {
    printf("{\"download_time\":%d,\"status\":\"installed\"}", time);
}

int main() {
    // Simulate async download with callback
    download_update(2000, install_update);
    return 0;
}