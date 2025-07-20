/*
7_owned-struct-类型.md
创建owned struct Table实例并初始化rows和columns
*/
#include <stdio.h>
#include <stdlib.h>

struct Table {
    int rows;
    int columns;
};

int main() {
    struct Table table = {.rows = 5, .columns = 10};
    
    printf("Table rows: %d, columns: %d\n", table.rows, table.columns);
    
    return 0;
}