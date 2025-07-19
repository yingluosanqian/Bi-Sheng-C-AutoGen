/*
1_泛型.md
泛型结构体实现简单的键值对，支持任意类型键值
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard C requires separate structures for each type combination */
struct IntStringPair {
    int key;
    char* value;
};

struct FloatIntPair {
    float key;
    int value;
};

void print_int_string_pair(struct IntStringPair* pair) {
    printf("Key: %d, Value: %s\n", pair->key, pair->value);
}

void print_float_int_pair(struct FloatIntPair* pair) {
    printf("Key: %.2f, Value: %d\n", pair->key, pair->value);
}

int main() {
    struct IntStringPair pair1 = {42, "Hello"};
    struct FloatIntPair pair2 = {3.14f, 100};
    
    print_int_string_pair(&pair1);
    print_float_int_pair(&pair2);
    
    return 0;
}