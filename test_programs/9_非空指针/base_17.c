/* Pointer Arithmetic */
#include <stdio.h>

int main() {
    int arr[3] = {100, 200, 300};
    int *ptr = arr;
    ptr++;
    printf("{result: %d}\n", *ptr);
    return 0;
}