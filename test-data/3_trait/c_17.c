/*
3_trait.md
trait指针变量与NULL进行比较判断
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    void *ptr = NULL;
    if (ptr == NULL) {
        return 0;
    }
    return 1;
}