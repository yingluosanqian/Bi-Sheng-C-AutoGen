/*
4_无栈协程.md
async函数实现简单的产品搜索
*/
#include <stdio.h>
#include <stdlib.h>

struct Product {
    char* name;
    float price;
};

struct Product* search_products_callback(char* query, void (*callback)(struct Product*)) {
    // Simulate async search
    struct Product* result = malloc(sizeof(struct Product));
    result->name = "Sample Product";
    result->price = 9.99;
    callback(result);
    return result;
}

void print_product(struct Product* p) {
    printf("{\"name\":\"%s\",\"price\":%.2f}", p->name, p->price);
}

int main() {
    search_products_callback("sample", print_product);
    return 0;
}