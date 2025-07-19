/*
4_无栈协程.md
async函数处理缓存写入模拟
*/
#include <stdio.h>
#include <stdlib.h>

void simulate_delay(int ms) {
    // Simulate delay (in real code this would use platform-specific sleep)
    for (volatile int i = 0; i < ms * 10000; i++);
}

void write_to_cache(const char* data) {
    simulate_delay(100);
    printf("{\"data\": \"%s\", \"status\": \"cached\"}", data);
}

int main() {
    write_to_cache("sample data");
    return 0;
}