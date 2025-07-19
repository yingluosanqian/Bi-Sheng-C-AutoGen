/*
8_运算符重载.md
重载^运算符实现数据加密
*/
#include <stdio.h>
#include <string.h>

struct EncryptedString {
    char *data;
    int length;
};

// Standard C requires explicit function calls
struct EncryptedString xor_encrypt(struct EncryptedString s, char key) {
    for (int i = 0; i < s.length; i++) {
        s.data[i] ^= key;
    }
    return s;
}

int main() {
    char message[] = "Hello World";
    char key = 'K';
    
    struct EncryptedString encrypted = {
        .data = message,
        .length = strlen(message)
    };
    
    // Must call function explicitly
    encrypted = xor_encrypt(encrypted, key);
    printf("Encrypted: %s\n", encrypted.data);
    
    // Decrypt by applying XOR again
    encrypted = xor_encrypt(encrypted, key);
    printf("Decrypted: %s\n", encrypted.data);
    
    return 0;
}
