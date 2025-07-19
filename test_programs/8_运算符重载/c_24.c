/*
8_运算符重载.md
重载-运算符实现日期差值
*/
#include <stdio.h>

struct Date {
    int year;
    int month;
    int day;
};

int days_until_month(int month) {
    static int cum_days[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    if (month < 1 || month > 12) return 0;
    return cum_days[month-1];
}

int date_diff(struct Date d1, struct Date d2) {
    int total1 = d1.day + days_until_month(d1.month);
    int total2 = d2.day + days_until_month(d2.month);
    int diff = total1 - total2;
    return diff < 0 ? -diff : diff;
}

int main() {
    struct Date d1 = {2023, 1, 1};
    struct Date d2 = {2023, 1, 10};
    printf("%d\n", date_diff(d1, d2));
    return 0;
}