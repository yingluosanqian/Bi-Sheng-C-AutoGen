/*
4_无栈协程.md
async函数实现简单的数据库插入模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct DatabaseResult {
    int success;
    int inserted_id;
};

struct DatabaseResult insert_data(const char* data) {
    // Simulate database insertion
    struct DatabaseResult result;
    result.success = 1;
    result.inserted_id = 42;
    return result;
}

int main() {
    struct DatabaseResult result = insert_data("test data");
    printf("{\"success\":%d,\"inserted_id\":%d}", result.success, result.inserted_id);
    return 0;
}