/*
1_泛型.md
常量泛型实现固定长度字符串结构体，长度可配置
*/
#include <stdio.h>
#include <string.h>

/* Standard C approach - need separate structures for different lengths */
struct FixedString10 {
    char data[10];
    int length;
};

struct FixedString20 {
    char data[20];
    int length;
};

void init_string10(struct FixedString10 *str, const char *input) {
    int len = strlen(input);
    if (len >= 10) len = 9;
    strncpy(str->data, input, len);
    str->data[len] = '\0';
    str->length = len;
}

void init_string20(struct FixedString20 *str, const char *input) {
    int len = strlen(input);
    if (len >= 20) len = 19;
    strncpy(str->data, input, len);
    str->data[len] = '\0';
    str->length = len;
}

void print_string10(struct FixedString10 *str) {
    printf("%s\n", str->data);
}

void print_string20(struct FixedString20 *str) {
    printf("%s\n", str->data);
}

int main() {
    struct FixedString10 str1;
    struct FixedString20 str2;
    
    init_string10(&str1, "Hello");
    init_string20(&str2, "World!");
    
    print_string10(&str1);
    print_string20(&str2);
    
    return 0;
}