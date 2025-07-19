/*
7_owned-struct-类型.md
定义owned struct Table，包含rows和columns成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Table {
    int rows;
    int columns;
};

void print_table(struct Table *t) {
    printf("Table: %d rows, %d columns\n", t->rows, t->columns);
}

int main() {
    struct Table my_table = {5, 3};
    print_table(&my_table);
    return 0;
}