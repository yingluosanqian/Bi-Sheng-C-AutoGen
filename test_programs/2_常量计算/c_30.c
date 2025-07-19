/*
2_常量计算.md
constexpr if实现编译时条件分支选择
*/
#include <stdio.h>

int handle_int_case(int value) {
    printf("Handling integer: %d\n", value);
    return value * 2;
}

int handle_pointer_case(int* ptr) {
    printf("Handling pointer: %d\n", *ptr);
    return (*ptr) * 3;
}

int main() {
    int value = 10;
    int* ptr = &value;
    
    // Runtime branching - both functions exist in final binary
    int result1 = handle_int_case(value);
    int result2 = handle_pointer_case(ptr);
    
    printf("Results: %d, %d\n", result1, result2);
    return 0;
}