/* Null Pointer Initialization */
#include <stdio.h>

int main() {
    int *ptr = NULL;
    if (ptr == NULL) {
        printf("{result: pointer is null}\n");
    } else {
        printf("{result: pointer is not null}\n");
    }
    return 0;
}