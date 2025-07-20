/*
7_owned-struct-类型.md
创建owned struct Date实例并初始化day、month和year
*/
#include <stdio.h>
#include <stdlib.h>

struct Date {
    int day;
    int month;
    int year;
};

void print_date(struct Date *date) {
    printf("Date: %d/%d/%d\n", date->day, date->month, date->year);
}

int main() {
    struct Date date = {.day = 15, .month = 8, .year = 2023};
    print_date(&date);
    return 0;
}