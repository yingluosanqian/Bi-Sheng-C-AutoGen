/*
8_运算符重载.md
重载>运算符比较两个哈希值
*/
#include <stdio.h>

struct Hash {
    unsigned char data[16];
};

int compare_hash(struct Hash a, struct Hash b) {
    for (int i = 0; i < 16; i++) {
        if (a.data[i] != b.data[i])
            return a.data[i] > b.data[i];
    }
    return 0;
}

int main() {
    struct Hash hash1 = {{0x00, 0x11, 0x22, 0x33}};
    struct Hash hash2 = {{0x00, 0x11, 0x22, 0x44}};
    
    printf("%d\n", compare_hash(hash1, hash2));
    printf("%d\n", compare_hash(hash2, hash1));
    
    return 0;
}