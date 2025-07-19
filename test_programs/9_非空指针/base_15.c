/* Pointer to a Constant (const int *) */
#include <stdio.h>

int main() {
    int val = 60;
    const int *ptr = &val;
    val = 65;
    printf("{result: %d}\n", *ptr);
    return 0;
}