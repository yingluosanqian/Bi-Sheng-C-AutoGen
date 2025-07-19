/*
10_标准库.md
使用Weak创建一个弱引用指针
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int* strong_ref_count;
} Data;

int main(void) {
    Data* data = malloc(sizeof(Data));
    data->value = 42;
    data->strong_ref_count = malloc(sizeof(int));
    *data->strong_ref_count = 1;
    
    // Create weak reference (simulated)
    Data* weak_ref = data;
    
    // Check if weak reference is valid
    if (*data->strong_ref_count > 0) {
        printf("%d\n", weak_ref->value);
    }
    
    // Clean up
    (*data->strong_ref_count)--;
    if (*data->strong_ref_count == 0) {
        free(data);
    }
    free(data->strong_ref_count);
    
    return 0;
}