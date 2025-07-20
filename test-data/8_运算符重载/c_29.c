/*
8_运算符重载.md
重载|运算符实现权限组合
*/
#include <stdio.h>

typedef struct {
    int value;
} Permissions;

Permissions combine_permissions(Permissions p1, Permissions p2) {
    Permissions result;
    result.value = p1.value | p2.value;
    return result;
}

int main() {
    Permissions read = {1};
    Permissions write = {2};
    Permissions rw = combine_permissions(read, write);
    printf("%d", rw.value);
    return 0;
}