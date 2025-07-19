/*
1_泛型.md
常量泛型实现固定大小的位图，位数可配置
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Fixed-size bitmap for 32 bits */
struct Bitmap32 {
    unsigned int data[1]; /* 32 bits = 1 * 32 */
};

/* Fixed-size bitmap for 64 bits */
struct Bitmap64 {
    unsigned int data[2]; /* 64 bits = 2 * 32 */
};

void bitmap32_set(struct Bitmap32 *bitmap, int bit) {
    if (bit >= 0 && bit < 32) {
        int word_index = bit / 32;
        int bit_index = bit % 32;
        bitmap->data[word_index] |= (1U << bit_index);
    }
}

void bitmap64_set(struct Bitmap64 *bitmap, int bit) {
    if (bit >= 0 && bit < 64) {
        int word_index = bit / 32;
        int bit_index = bit % 32;
        bitmap->data[word_index] |= (1U << bit_index);
    }
}

int bitmap32_get(struct Bitmap32 *bitmap, int bit) {
    if (bit >= 0 && bit < 32) {
        int word_index = bit / 32;
        int bit_index = bit % 32;
        return (bitmap->data[word_index] & (1U << bit_index)) != 0;
    }
    return 0;
}

int bitmap64_get(struct Bitmap64 *bitmap, int bit) {
    if (bit >= 0 && bit < 64) {
        int word_index = bit / 32;
        int bit_index = bit % 32;
        return (bitmap->data[word_index] & (1U << bit_index)) != 0;
    }
    return 0;
}

int main() {
    struct Bitmap32 bmp32;
    struct Bitmap64 bmp64;
    
    memset(&bmp32, 0, sizeof(bmp32));
    memset(&bmp64, 0, sizeof(bmp64));
    
    bitmap32_set(&bmp32, 5);
    bitmap32_set(&bmp32, 15);
    
    bitmap64_set(&bmp64, 10);
    bitmap64_set(&bmp64, 50);
    
    printf("32-bit bitmap: bit 5 = %d, bit 15 = %d\n", 
           bitmap32_get(&bmp32, 5), bitmap32_get(&bmp32, 15));
    printf("64-bit bitmap: bit 10 = %d, bit 50 = %d\n", 
           bitmap64_get(&bmp64, 10), bitmap64_get(&bmp64, 50));
    
    return 0;
}