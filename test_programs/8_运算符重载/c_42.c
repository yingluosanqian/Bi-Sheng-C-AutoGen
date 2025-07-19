/*
8_运算符重载.md
重载<运算符比较两个文件大小
*/
#include <stdio.h>

typedef struct {
    long size;
} File;

int compareFiles(File a, File b) {
    return a.size < b.size;
}

int main() {
    File file1 = {100};
    File file2 = {200};
    int result = compareFiles(file1, file2);
    printf("%d\n", result);
    return 0;
}