/* Multilevel Pointer (Pointer to Pointer) */
#include <stdio.h>

int main() {
    int var = 50;
    int *p = &var;
    int **pp = &p;
    **pp = 55;
    printf("{result: %d}\n", **pp);
    return 0;
}