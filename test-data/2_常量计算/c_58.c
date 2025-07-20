/*
2_常量计算.md
综合应用：编译时配置系统使用所有constexpr特性
*/
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 8
#define USE_INT_TYPE 1
#define ENABLE_VALIDATION 1

int calculate_capacity() {
    return BUFFER_SIZE * 2;
}

int is_valid_size(int size) {
    return size > 0 && size <= 16;
}

void process_buffer() {
    int buffer[BUFFER_SIZE];
    int capacity = calculate_capacity();
    
    for (int i = 0; i < BUFFER_SIZE; i++) {
        buffer[i] = i + 1;
    }
    
    printf("Buffer configured: size=%d, capacity=%d\n", BUFFER_SIZE, capacity);
    
    if (USE_INT_TYPE) {
        printf("Using integer type\n");
    } else {
        printf("Using generic type\n");
    }
    
    if (ENABLE_VALIDATION && is_valid_size(BUFFER_SIZE)) {
        printf("Validation enabled and passed\n");
    } else {
        printf("Validation disabled or failed\n");
    }
    
    printf("Sum: %d\n", (BUFFER_SIZE * (BUFFER_SIZE + 1)) / 2);
}

int main() {
    process_buffer();
    return 0;
}