/*
4_无栈协程.md
async函数处理快递追踪模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Package {
    int id;
    char status[50];
};

struct Package track_package_sync(int id) {
    struct Package pkg = {id, "In transit"};
    return pkg;
}

int main() {
    struct Package pkg = track_package_sync(12345);
    printf("{\"id\": %d, \"status\": \"%s\"}", pkg.id, pkg.status);
    return 0;
}