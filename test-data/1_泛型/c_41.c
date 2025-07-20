/*
1_泛型.md
泛型类型别名定义数组类型，简化数组声明
*/
#include <stdio.h>
#include <stdlib.h>

int main() {
    // Standard C requires explicit array declarations for each type and size
    int int_array_5[5] = {1, 2, 3, 4, 5};
    float float_array_3[3] = {1.1, 2.2, 3.3};
    double double_array_4[4] = {1.0, 2.0, 3.0, 4.0};
    char char_array_10[10] = "Hello";
    
    // Print array contents
    printf("Int array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", int_array_5[i]);
    }
    printf("\n");
    
    printf("Float array: ");
    for (int i = 0; i < 3; i++) {
        printf("%.1f ", float_array_3[i]);
    }
    printf("\n");
    
    printf("Double array: ");
    for (int i = 0; i < 4; i++) {
        printf("%.1f ", double_array_4[i]);
    }
    printf("\n");
    
    printf("Char array: %s\n", char_array_10);
    
    return 0;
}