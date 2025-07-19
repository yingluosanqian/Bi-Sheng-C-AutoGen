/*
7_owned-struct-类型.md
定义owned struct Address，包含street和city成员
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