/*
1_泛型.md
泛型联合体实现内存视图，支持不同类型的内存解释
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef union {
    uint32_t as_uint32;
    int32_t as_int32;
    float as_float;
    uint8_t as_bytes[4];
} IntMemoryView;

typedef union {
    uint64_t as_uint64;
    int64_t as_int64;
    double as_double;
    uint8_t as_bytes[8];
} LongMemoryView;

void print_int_memory_view(IntMemoryView* view) {
    printf("uint32: %u\n", view->as_uint32);
    printf("int32: %d\n", view->as_int32);
    printf("float: %.2f\n", view->as_float);
    printf("bytes: %02x %02x %02x %02x\n", 
           view->as_bytes[0], view->as_bytes[1], 
           view->as_bytes[2], view->as_bytes[3]);
}

void print_long_memory_view(LongMemoryView* view) {
    printf("uint64: %lu\n", view->as_uint64);
    printf("int64: %ld\n", view->as_int64);
    printf("double: %.2f\n", view->as_double);
    printf("bytes: %02x %02x %02x %02x %02x %02x %02x %02x\n",
           view->as_bytes[0], view->as_bytes[1], view->as_bytes[2], view->as_bytes[3],
           view->as_bytes[4], view->as_bytes[5], view->as_bytes[6], view->as_bytes[7]);
}

int main() {
    IntMemoryView int_view;
    int_view.as_float = 3.14f;
    printf("32-bit Memory View:\n");
    print_int_memory_view(&int_view);
    
    LongMemoryView long_view;
    long_view.as_double = 2.718281828;
    printf("\n64-bit Memory View:\n");
    print_long_memory_view(&long_view);
    
    return 0;
}