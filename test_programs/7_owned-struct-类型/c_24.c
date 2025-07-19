/*
7_owned-struct-类型.md
25. Define owned struct 'BankAccount' with accountNumber and balance
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int accountNumber;
    double balance;
} BankAccount;

void printAccount(BankAccount *account) {
    printf("Account Number: %d\nBalance: %.2f\n", account->accountNumber, account->balance);
}

int main() {
    BankAccount account = {12345, 1000.50};
    printAccount(&account);
    return 0;
}