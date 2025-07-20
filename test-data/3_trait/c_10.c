/*
3_trait.md
定义泛型trait Container<T>，为Array结构体实现add和get方法
*/
#include <stdio.h>
#include <stdlib.h>

struct Array {
    int* data;
    size_t size;
    size_t capacity;
};

void Array_init(struct Array* this, size_t capacity) {
    this->data = malloc(capacity * sizeof(int));
    this->size = 0;
    this->capacity = capacity;
}

void Array_add(struct Array* this, int value) {
    if (this->size < this->capacity) {
        this->data[this->size++] = value;
    }
}

int Array_get(struct Array* this, size_t index) {
    if (index < this->size) {
        return this->data[index];
    }
    return 0;
}

void Array_free(struct Array* this) {
    free(this->data);
}

int main() {
    struct Array arr;
    Array_init(&arr, 10);
    
    Array_add(&arr, 42);
    Array_add(&arr, 100);
    
    printf("%d\n", Array_get(&arr, 0));
    printf("%d\n", Array_get(&arr, 1));
    
    Array_free(&arr);
    return 0;
}