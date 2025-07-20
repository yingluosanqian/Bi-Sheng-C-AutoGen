/*
0_成员函数.md
为struct String添加compare成员函数，字符串比较
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
    char* data;
    size_t length;
};

int string_compare(struct String* str1, struct String* str2) {
    if (str1->length != str2->length) {
        return (str1->length > str2->length) ? 1 : -1;
    }
    return strcmp(str1->data, str2->data);
}

struct String create_string(const char* str) {
    struct String s;
    s.length = strlen(str);
    s.data = malloc(s.length + 1);
    strcpy(s.data, str);
    return s;
}

void free_string(struct String* str) {
    free(str->data);
    str->data = NULL;
    str->length = 0;
}

int main() {
    struct String str1 = create_string("hello");
    struct String str2 = create_string("world");
    struct String str3 = create_string("hello");
    
    int result1 = string_compare(&str1, &str2);
    int result2 = string_compare(&str1, &str3);
    int result3 = string_compare(&str2, &str1);
    
    printf("Comparing 'hello' with 'world': %d\n", result1);
    printf("Comparing 'hello' with 'hello': %d\n", result2);
    printf("Comparing 'world' with 'hello': %d\n", result3);
    
    free_string(&str1);
    free_string(&str2);
    free_string(&str3);
    
    return 0;
}