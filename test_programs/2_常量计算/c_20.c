/*
2_常量计算.md
使用rank计算多维数组的维数
*/
#include <stdio.h>

// In standard C, we need to manually track array dimensions
// or use macros to calculate them
#define RANK_1D 1
#define RANK_2D 2
#define RANK_3D 3

int main() {
    int arr1[5];
    int arr2[3][4];
    int arr3[2][3][4];
    
    // Manual dimension tracking
    int rank1 = RANK_1D;
    int rank2 = RANK_2D;
    int rank3 = RANK_3D;
    
    printf("%d\n", rank1);
    printf("%d\n", rank2);
    printf("%d\n", rank3);
    
    return 0;
}