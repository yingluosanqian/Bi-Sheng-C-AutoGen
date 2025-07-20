/*
0_成员函数.md
为struct Account添加deposit成员函数，存款操作
*/
#include <stdio.h>
#include <stdlib.h>

struct Account {
    char* name;
    double balance;
};

// In standard C, we need to define a separate function
void deposit(struct Account* account, double amount) {
    if (amount > 0) {
        account->balance += amount;
        printf("Deposited %.2f to %s's account. New balance: %.2f\n", 
               amount, account->name, account->balance);
    } else {
        printf("Error: Cannot deposit negative or zero amount\n");
    }
}

int main() {
    struct Account account = {"John Doe", 1000.0};
    
    printf("Initial balance for %s: %.2f\n", account.name, account.balance);
    
    // In standard C, we need to pass the account pointer explicitly
    deposit(&account, 500.0);
    deposit(&account, -50.0);  // This should fail
    
    printf("Final balance: %.2f\n", account.balance);
    
    return 0;
}
