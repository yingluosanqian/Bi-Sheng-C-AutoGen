/*
4_无栈协程.md
async函数实现简单的数据库更新模拟
*/
#include <stdio.h>
#include <stdlib.h>

// Mock database update function
int update_database(int value) {
    // Simulate database update
    return value * 2;
}

// Synchronous wrapper for async simulation
int main() {
    int original_value = 42;
    int updated_value = update_database(original_value);
    
    printf("{\"original\": %d, \"updated\": %d}", original_value, updated_value);
    return 0;
}