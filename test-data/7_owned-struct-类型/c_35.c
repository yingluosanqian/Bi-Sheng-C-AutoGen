/*
7_owned-struct-类型.md
创建owned struct BankAccount实例并初始化number和balance
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    float balance;
} BankAccount;

void print_account(BankAccount *account) {
    printf("Account number: %d, Balance: %.2f\n", account->number, account->balance);
}

int main() {
    BankAccount account = {12345, 1000.50f};
    print_account(&account);
    return 0;
}