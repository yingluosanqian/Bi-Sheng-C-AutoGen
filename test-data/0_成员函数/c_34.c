/*
0_成员函数.md
为struct String添加concat成员函数，字符串连接
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct String {
    char* data;
    size_t length;
};

struct String* string_concat(struct String* str1, const struct String* str2) {
    if (!str1 || !str2 || !str2->data) {
        return str1;
    }
    
    size_t new_length = str1->length + str2->length;
    char* new_data = (char*)realloc(str1->data, new_length + 1);
    if (!new_data) {
        return str1;
    }
    
    str1->data = new_data;
    strcat(str1->data, str2->data);
    str1->length = new_length;
    
    return str1;
}

struct String create_string(const char* str) {
    struct String s;
    s.length = strlen(str);
    s.data = (char*)malloc(s.length + 1);
    strcpy(s.data, str);
    return s;
}

void free_string(struct String* s) {
    if (s && s->data) {
        free(s->data);
        s->data = NULL;
        s->length = 0;
    }
}

int main() {
    struct String str1 = create_string("Hello ");
    struct String str2 = create_string("World!");
    
    string_concat(&str1, &str2);
    
    printf("%s\n", str1.data);
    
    free_string(&str1);
    free_string(&str2);
    
    return 0;
}