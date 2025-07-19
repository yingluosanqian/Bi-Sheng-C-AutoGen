/*
4_无栈协程.md
async函数处理文件写入模拟
*/
#include <stdio.h>
#include <stdlib.h>

void write_to_file(const char* filename, const char* content, void (*callback)(int)) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        callback(0);
        return;
    }
    
    int result = fputs(content, file);
    fclose(file);
    callback(result != EOF);
}

void on_write_complete(int success) {
    if (success) {
        printf("{\"status\": \"success\"}");
    } else {
        printf("{\"status\": \"failed\"}");
    }
}

int main() {
    write_to_file("output.txt", "Hello World", on_write_complete);
    return 0;
}