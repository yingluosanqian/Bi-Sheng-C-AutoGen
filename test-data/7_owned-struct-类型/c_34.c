/*
7_owned-struct-类型.md
定义owned struct BankAccount，包含number和balance成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int number;
    double balance;
} BankAccount;

void deposit(BankAccount *account, double amount) {
    account->balance += amount;
}

double get_balance(const BankAccount *account) {
    return account->balance;
}

int main() {
    BankAccount account = {12345, 1000.0};
    
    printf("Initial balance: %.2f\n", get_balance(&account));
    deposit(&account, 500.0);
    printf("After deposit: %.2f\n", get_balance(&account));
    
    return 0;
}