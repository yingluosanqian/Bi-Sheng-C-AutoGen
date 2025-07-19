/*
0_成员函数.md
为int类型添加to_binary静态成员函数，转换为二进制字符串
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* int_to_binary(int value) {
    if (value == 0) {
        char* result = (char*)malloc(2);
        strcpy(result, "0");
        return result;
    }
    
    int temp = value < 0 ? -value : value;
    int bits = 0;
    int temp_copy = temp;
    while (temp_copy > 0) {
        bits++;
        temp_copy >>= 1;
    }
    
    if (value < 0) bits++;
    
    char* result = (char*)malloc(bits + 1);
    result[bits] = '\0';
    
    temp = value < 0 ? -value : value;
    for (int i = bits - 1; i >= (value < 0 ? 1 : 0); i--) {
        result[i] = (temp & 1) ? '1' : '0';
        temp >>= 1;
    }
    
    if (value < 0) {
        result[0] = '-';
    }
    
    return result;
}

int main() {
    int numbers[] = {5, 10, 0, -3};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    
    for (int i = 0; i < count; i++) {
        char* binary = int_to_binary(numbers[i]);
        printf("%d in binary: %s\n", numbers[i], binary);
        free(binary);
    }
    
    return 0;
}