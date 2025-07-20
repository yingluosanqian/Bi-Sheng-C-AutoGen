/*测试可空指针 (Nullable Pointer) 与判空*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    int value = 200;
    int *p_nullable = NULL;
    
    if (1) {
        p_nullable = &value;
    }
    
    if (p_nullable != NULL) {
        *p_nullable = 210;
        printf("{result: %d}\n", *p_nullable);
    } else {
        printf("{result: pointer is null}\n");
    }
    return 0;
}