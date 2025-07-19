/*
6_内存安全.md
安全区迭代器示例：安全的集合遍历
*/
#include <stdio.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers)/sizeof(numbers[0]);
    
    for (size_t i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    return 0;
}