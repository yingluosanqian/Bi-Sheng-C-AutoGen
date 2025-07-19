/*
8_运算符重载.md
重载<运算符比较两个文件名顺序
*/
#include <stdio.h>
#include <string.h>

typedef struct {
    char* name;
} Filename;

int compare_filenames(Filename f1, Filename f2) {
    return strcmp(f1.name, f2.name) < 0;
}

int main() {
    Filename file1 = {"document.txt"};
    Filename file2 = {"archive.pdf"};
    
    int result = compare_filenames(file1, file2);
    printf("%d", result);
    return 0;
}