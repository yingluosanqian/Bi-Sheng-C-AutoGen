/*
7_owned-struct-类型.md
13. Define owned struct 'Date' with day, month, and year fields
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