/*访问和修改一个整数*/

#include <stdio.h>
#include <stdlib.h>

int main() {
    int value = 42;
    int *ptr = &value;
    *ptr = 100;
    printf("{result: %d}", *ptr);
    return 0;
}