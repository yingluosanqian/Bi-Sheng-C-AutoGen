/*
7_owned-struct-类型.md
创建owned struct Address实例并初始化street和city
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address {
    char street[50];
    char city[50];
};

void print_address(struct Address *addr) {
    printf("{\"street\":\"%s\", \"city\":\"%s\"}", addr->street, addr->city);
}

int main() {
    struct Address addr;
    strcpy(addr.street, "123 Main St");
    strcpy(addr.city, "Springfield");
    
    print_address(&addr);
    return 0;
}