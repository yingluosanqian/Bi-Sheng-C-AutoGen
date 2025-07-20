/*
7_owned-struct-类型.md
创建owned struct Book实例并初始化title和author
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    char title[100];
    char author[100];
};

int main() {
    struct Book book;
    strcpy(book.title, "The C Programming Language");
    strcpy(book.author, "Brian W. Kernighan and Dennis M. Ritchie");
    
    printf("Book: %s by %s\n", book.title, book.author);
    return 0;
}