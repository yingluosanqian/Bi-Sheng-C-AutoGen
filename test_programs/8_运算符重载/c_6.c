/*
8_运算符重载.md
重载!=运算符检查两个日期是否不同
*/
#include <stdio.h>

struct Date {
    int day;
    int month;
    int year;
};

int dates_not_equal(struct Date d1, struct Date d2) {
    return d1.day != d2.day || d1.month != d2.month || d1.year != d2.year;
}

int main() {
    struct Date date1 = {15, 7, 2023};
    struct Date date2 = {15, 7, 2024};
    
    printf("%d", dates_not_equal(date1, date2));
    return 0;
}