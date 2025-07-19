/*
7_owned-struct-类型.md
49. Define owned struct 'ContactInfo' with phone and address
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char phone[20];
    char address[100];
} ContactInfo;

void print_contact_info(const ContactInfo* info) {
    printf("Phone: %s\nAddress: %s\n", info->phone, info->address);
}

int main() {
    ContactInfo contact = {
        .phone = "123-456-7890",
        .address = "123 Main St, City"
    };
    
    print_contact_info(&contact);
    return 0;
}