/*
1_泛型.md
泛型结构体实现二元组，存储两个任意类型的值
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we have to use void pointers to create a generic tuple
typedef struct {
    void* first;
    void* second;
    int first_type_size;
    int second_type_size;
} Tuple;

// Function to create a tuple
Tuple* create_tuple(void* first, int first_size, void* second, int second_size) {
    Tuple* tuple = (Tuple*)malloc(sizeof(Tuple));
    
    tuple->first = malloc(first_size);
    tuple->second = malloc(second_size);
    
    memcpy(tuple->first, first, first_size);
    memcpy(tuple->second, second, second_size);
    
    tuple->first_type_size = first_size;
    tuple->second_type_size = second_size;
    
    return tuple;
}

// Function to free a tuple
void free_tuple(Tuple* tuple) {
    free(tuple->first);
    free(tuple->second);
    free(tuple);
}

// Function to get values (caller must know the types)
void* get_first(Tuple* tuple) {
    return tuple->first;
}

void* get_second(Tuple* tuple) {
    return tuple->second;
}

int main() {
    int i = 42;
    float f = 3.14;
    
    // Create tuple of int and float
    Tuple* tuple = create_tuple(&i, sizeof(int), &f, sizeof(float));
    
    // Get values (need to cast to correct types)
    int* i_ptr = (int*)get_first(tuple);
    float* f_ptr = (float*)get_second(tuple);
    
    // Print values
    printf("Tuple values: %d, %.2f\n", *i_ptr, *f_ptr);
    
    // Clean up
    free_tuple(tuple);
    
    return 0;
}