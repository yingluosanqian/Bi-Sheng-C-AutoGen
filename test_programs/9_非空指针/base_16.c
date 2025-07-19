/* Constant Pointer to a Variable (int * const) */
#include <stdio.h>

int main() {
    int val1 = 70;
    int * const ptr = &val1;
    *ptr = 75;
    printf("{result: %d}\n", *ptr);
    return 0;
}