/*
4_无栈协程.md
async函数实现简单的数据库删除模拟
*/
#include <stdio.h>
#include <stdlib.h>

int delete_from_db(int id) {
    // Simulate database delete operation
    printf("{\"status\": \"success\", \"deleted_id\": %d}", id);
    return 0;
}

int main() {
    delete_from_db(42);
    return 0;
}