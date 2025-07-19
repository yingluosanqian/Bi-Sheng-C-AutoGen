/*
8_运算符重载.md
重载!=运算符检查两个账户是否不同
*/
#include <stdio.h>

typedef struct {
    int id;
} Account;

int accountsNotEqual(Account a, Account b) {
    return a.id != b.id;
}

int main() {
    Account acc1 = {100};
    Account acc2 = {200};
    int result = accountsNotEqual(acc1, acc2);
    printf("%d\n", result);
    return 0;
}