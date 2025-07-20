/*
7_owned-struct-类型.md
14. Create owned struct 'Account' with balance and owner fields
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    double balance;
    char owner[50];
};

void print_account(struct Account *account) {
    printf("Account owner: %s\n", account->owner);
    printf("Account balance: %.2f\n", account->balance);
}

int main() {
    struct Account account;
    account.balance = 1000.50;
    strcpy(account.owner, "John Doe");
    
    print_account(&account);
    
    return 0;
}