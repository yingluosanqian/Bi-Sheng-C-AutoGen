/*
2_常量计算.md
使用constexpr定义编译时整数常量，并在数组长度中使用
*/
#include <stdio.h>

#define ARRAY_SIZE 5

int main() {
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5};
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}