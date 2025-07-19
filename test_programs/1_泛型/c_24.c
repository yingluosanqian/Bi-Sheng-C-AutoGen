/*
1_泛型.md
常量泛型实现固定大小的缓冲区，大小可配置
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Standard C approach - separate structures for different sizes */
struct Buffer10 {
    char data[10];
    int size;
    int capacity;
};

struct Buffer20 {
    char data[20];
    int size;
    int capacity;
};

void init_buffer10(struct Buffer10 *buf) {
    memset(buf->data, 0, 10);
    buf->size = 0;
    buf->capacity = 10;
}

void init_buffer20(struct Buffer20 *buf) {
    memset(buf->data, 0, 20);
    buf->size = 0;
    buf->capacity = 20;
}

int add_to_buffer10(struct Buffer10 *buf, char c) {
    if (buf->size >= buf->capacity) {
        return 0;
    }
    buf->data[buf->size++] = c;
    return 1;
}

int add_to_buffer20(struct Buffer20 *buf, char c) {
    if (buf->size >= buf->capacity) {
        return 0;
    }
    buf->data[buf->size++] = c;
    return 1;
}

void print_buffer10(struct Buffer10 *buf) {
    printf("Buffer capacity: %d, size: %d, data: ", buf->capacity, buf->size);
    for (int i = 0; i < buf->size; i++) {
        printf("%c", buf->data[i]);
    }
    printf("\n");
}

void print_buffer20(struct Buffer20 *buf) {
    printf("Buffer capacity: %d, size: %d, data: ", buf->capacity, buf->size);
    for (int i = 0; i < buf->size; i++) {
        printf("%c", buf->data[i]);
    }
    printf("\n");
}

int main() {
    struct Buffer10 buf1;
    struct Buffer20 buf2;
    
    init_buffer10(&buf1);
    init_buffer20(&buf2);
    
    add_to_buffer10(&buf1, 'H');
    add_to_buffer10(&buf1, 'i');
    
    add_to_buffer20(&buf2, 'W');
    add_to_buffer20(&buf2, 'o');
    add_to_buffer20(&buf2, 'r');
    add_to_buffer20(&buf2, 'l');
    add_to_buffer20(&buf2, 'd');
    
    print_buffer10(&buf1);
    print_buffer20(&buf2);
    
    return 0;
}