/*
0_成员函数.md
为int类型添加print成员函数，打印整数值
*/
#include <stdio.h>

// In standard C, we can't add member functions to primitive types
// So we need to use a global function instead
void print_int(int* value) {
    printf("%d\n", *value);
}

int main() {
    int number = 42;
    
    // Call the global function to print the integer
    print_int(&number);
    
    return 0;
}
