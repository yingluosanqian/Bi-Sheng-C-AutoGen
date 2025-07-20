/*
10_标准库.md
使用option_unwrap解包Option中的整数
*/
#include <stdio.h>

int main(void) {
    int *value = NULL; // Simulating None case
    
    // Unsafe unwrapping in C - could crash if value is NULL
    if (value != NULL) {
        printf("%d", *value);
    }
    
    return 0;
}