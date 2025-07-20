/*
3_trait.md
泛型trait List<T>为ArrayList结构体实现add和remove方法
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    size_t size;
    size_t capacity;
} ArrayList;

void ArrayList_init(ArrayList* this) {
    this->capacity = 10;
    this->size = 0;
    this->data = malloc(this->capacity * sizeof(int));
}

void ArrayList_add(ArrayList* this, int item) {
    if (this->size >= this->capacity) {
        this->capacity *= 2;
        this->data = realloc(this->data, this->capacity * sizeof(int));
    }
    this->data[this->size++] = item;
}

int ArrayList_remove(ArrayList* this, size_t index) {
    if (index >= this->size) return 0;
    int removed = this->data[index];
    for (size_t i = index; i < this->size - 1; i++) {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
    return removed;
}

int main() {
    ArrayList list;
    ArrayList_init(&list);
    
    ArrayList_add(&list, 10);
    ArrayList_add(&list, 20);
    ArrayList_add(&list, 30);
    
    ArrayList_remove(&list, 1);
    
    printf("Size: %zu\n", list.size);
    printf("Elements: %d, %d\n", list.data[0], list.data[1]);
    
    free(list.data);
    return 0;
}