/*
7_owned-struct-类型.md
50. Create owned struct 'InventoryItem' with ID and stockCount
*/
#include <stdio.h>
#include <stdlib.h>

struct InventoryItem {
    int id;
    int stockCount;
};

void printInventoryItem(struct InventoryItem item) {
    printf("ID: %d, Stock: %d\n", item.id, item.stockCount);
}

int main() {
    struct InventoryItem item = {.id = 1001, .stockCount = 42};
    printInventoryItem(item);
    return 0;
}