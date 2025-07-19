/*
2_常量计算.md
使用type trait和constexpr if实现自适应数据结构
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IntContainer {
    int data[10];
    int size;
};

struct PtrContainer {
    void** data;
    int size;
    int capacity;
};

void init_int_container(struct IntContainer* container) {
    container->size = 0;
    memset(container->data, 0, sizeof(container->data));
}

void init_ptr_container(struct PtrContainer* container) {
    container->data = malloc(10 * sizeof(void*));
    container->size = 0;
    container->capacity = 10;
}

void add_int(struct IntContainer* container, int value) {
    if (container->size < 10) {
        container->data[container->size++] = value;
    }
}

void add_ptr(struct PtrContainer* container, void* value) {
    if (container->size < container->capacity) {
        container->data[container->size++] = value;
    }
}

int get_int_size(struct IntContainer* container) {
    return container->size;
}

int get_ptr_size(struct PtrContainer* container) {
    return container->size;
}

int main() {
    struct IntContainer int_container;
    struct PtrContainer ptr_container;
    
    init_int_container(&int_container);
    init_ptr_container(&ptr_container);
    
    add_int(&int_container, 42);
    add_int(&int_container, 24);
    
    int x = 100, y = 200;
    add_ptr(&ptr_container, &x);
    add_ptr(&ptr_container, &y);
    
    printf("Int container size: %d\n", get_int_size(&int_container));
    printf("Ptr container size: %d\n", get_ptr_size(&ptr_container));
    
    free(ptr_container.data);
    return 0;
}