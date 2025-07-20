/*
0_成员函数.md
为struct Account添加withdraw成员函数，取款操作
*/
#include <stdio.h>
#include <stdlib.h>

struct Account {
    int balance;
    char name[50];
};

int withdraw(struct Account* account, int amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        return 1;
    }
    return 0;
}

int main() {
    struct Account acc = {1000, "John"};
    
    printf("Initial balance: %d\n", acc.balance);
    
    if (withdraw(&acc, 300)) {
        printf("Withdrawal successful. New balance: %d\n", acc.balance);
    } else {
        printf("Withdrawal failed. Insufficient funds.\n");
    }
    
    if (withdraw(&acc, 800)) {
        printf("Withdrawal successful. New balance: %d\n", acc.balance);
    } else {
        printf("Withdrawal failed. Insufficient funds.\n");
    }
    
    return 0;
}