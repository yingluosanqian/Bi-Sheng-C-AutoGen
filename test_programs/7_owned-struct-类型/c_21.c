/*
7_owned-struct-类型.md
创建owned struct Phone实例并初始化number和type
*/
#include <stdio.h>
#include <stdlib.h>

struct Phone {
    char number[20];
    char type[20];
};

int main() {
    struct Phone my_phone = {
        .number = "123-456-7890",
        .type = "Mobile"
    };
    
    printf("Phone number: %s\n", my_phone.number);
    printf("Phone type: %s\n", my_phone.type);
    
    return 0;
}