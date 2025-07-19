/*
3_trait.md
实现Add trait使struct Vector支持向量加法
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Vector;

Vector add_vectors(Vector* v1, Vector* v2) {
    Vector result = {
        .x = v1->x + v2->x,
        .y = v1->y + v2->y
    };
    return result;
}

void print_vector(Vector* v) {
    printf("Vector(%d, %d)\n", v->x, v->y);
}

int main() {
    Vector v1 = {.x = 3, .y = 5};
    Vector v2 = {.x = 2, .y = 7};
    
    printf("Vector 1: ");
    print_vector(&v1);
    printf("Vector 2: ");
    print_vector(&v2);
    
    Vector sum = add_vectors(&v1, &v2);
    printf("Sum: ");
    print_vector(&sum);
    
    return 0;
}
