/*
3_trait.md
实现Deref trait使智能指针支持解引用
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* ptr;
} SmartIntPointer;

int SmartIntPointer_deref(SmartIntPointer* this) {
    return *(this->ptr);
}

void SmartIntPointer_free(SmartIntPointer* this) {
    free(this->ptr);
    this->ptr = NULL;
}

int main() {
    SmartIntPointer p;
    p.ptr = malloc(sizeof(int));
    *(p.ptr) = 42;
    
    printf("Dereferenced value: %d\n", SmartIntPointer_deref(&p));
    
    SmartIntPointer_free(&p);
    return 0;
}
