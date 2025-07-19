/*
8_运算符重载.md
重载->运算符实现智能指针访问
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* ptr;
} SmartInt;

SmartInt* create_smart_int(int value) {
    SmartInt* si = malloc(sizeof(SmartInt));
    si->ptr = malloc(sizeof(int));
    *si->ptr = value;
    return si;
}

void destroy_smart_int(SmartInt* si) {
    free(si->ptr);
    free(si);
}

// Manual access function in C
int* smart_int_get(SmartInt* si) {
    return si->ptr;
}

int main() {
    SmartInt* si = create_smart_int(42);
    
    // Manual access in C
    printf("Value: %d\n", *smart_int_get(si));
    *smart_int_get(si) = 100;
    printf("New value: %d\n", *smart_int_get(si));
    
    destroy_smart_int(si);
    return 0;
}
