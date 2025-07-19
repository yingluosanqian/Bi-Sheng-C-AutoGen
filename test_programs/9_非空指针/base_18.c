/* Pointer Comparison */
#include <stdio.h>

int main() {
    int arr[3] = {10, 20, 30};
    int *p1 = &arr[0];
    int *p2 = &arr[2];
    if (p1 < p2) {
        printf("{result: p1's address is less than p2's}\n");
    } else {
        printf("{result: p1's address is not less than p2's}\n");
    }
    return 0;
}