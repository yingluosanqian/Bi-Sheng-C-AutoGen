/*
1_泛型.md
常量泛型实现固定大小的环形缓冲区，大小可配置
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Circular buffer implementation in standard C
// We need to define a separate structure for each data type and size

// Define a circular buffer for integers with a specific size
#define BUFFER_SIZE 5

typedef struct {
    int data[BUFFER_SIZE];
    int head;
    int tail;
    int full;
} CircularBufferInt;

// Initialize the buffer
void init_buffer_int(CircularBufferInt* buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->full = 0;
}

// Check if the buffer is empty
int is_empty_int(CircularBufferInt* buffer) {
    return (!buffer->full && (buffer->head == buffer->tail));
}

// Check if the buffer is full
int is_full_int(CircularBufferInt* buffer) {
    return buffer->full;
}

// Push an item into the buffer
int push_int(CircularBufferInt* buffer, int item) {
    if (buffer->full) {
        return 0; // Buffer is full
    }

    buffer->data[buffer->head] = item;
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    buffer->full = (buffer->head == buffer->tail);
    return 1;
}

// Pop an item from the buffer
int pop_int(CircularBufferInt* buffer, int* item) {
    if (is_empty_int(buffer)) {
        return 0; // Buffer is empty
    }

    *item = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    buffer->full = 0;
    return 1;
}

// For a different data type or size, we would need to redefine everything
// For example, a float buffer would require:

typedef struct {
    float data[BUFFER_SIZE];
    int head;
    int tail;
    int full;
} CircularBufferFloat;

// Initialize the buffer
void init_buffer_float(CircularBufferFloat* buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->full = 0;
}

// Check if the buffer is empty
int is_empty_float(CircularBufferFloat* buffer) {
    return (!buffer->full && (buffer->head == buffer->tail));
}

// Check if the buffer is full
int is_full_float(CircularBufferFloat* buffer) {
    return buffer->full;
}

// Push an item into the buffer
int push_float(CircularBufferFloat* buffer, float item) {
    if (buffer->full) {
        return 0; // Buffer is full
    }

    buffer->data[buffer->head] = item;
    buffer->head = (buffer->head + 1) % BUFFER_SIZE;
    buffer->full = (buffer->head == buffer->tail);
    return 1;
}

// Pop an item from the buffer
int pop_float(CircularBufferFloat* buffer, float* item) {
    if (is_empty_float(buffer)) {
        return 0; // Buffer is empty
    }

    *item = buffer->data[buffer->tail];
    buffer->tail = (buffer->tail + 1) % BUFFER_SIZE;
    buffer->full = 0;
    return 1;
}

int main() {
    // Example usage with integer buffer
    CircularBufferInt int_buffer;
    init_buffer_int(&int_buffer);

    // Push items
    push_int(&int_buffer, 10);
    push_int(&int_buffer, 20);
    push_int(&int_buffer, 30);

    // Pop items
    int value;
    pop_int(&int_buffer, &value);
    printf("Popped: %d\n", value);
    pop_int(&int_buffer, &value);
    printf("Popped: %d\n", value);

    // Example usage with float buffer
    CircularBufferFloat float_buffer;
    init_buffer_float(&float_buffer);

    // Push items
    push_float(&float_buffer, 3.14);
    push_float(&float_buffer, 2.71);
    push_float(&float_buffer, 1.41);

    // Pop items
    float fvalue;
    pop_float(&float_buffer, &fvalue);
    printf("Popped: %.2f\n", fvalue);
    pop_float(&float_buffer, &fvalue);
    printf("Popped: %.2f\n", fvalue);

    return 0;
}