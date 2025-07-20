/*
1_泛型.md
泛型函数实现数组复制，支持任意类型数组
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Standard C requires separate functions for each data type
void copy_int_array(int* dest, const int* src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void copy_double_array(double* dest, const double* src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

void copy_char_array(char* dest, const char* src, int size) {
    for (int i = 0; i < size; i++) {
        dest[i] = src[i];
    }
}

int main() {
    // Integer array
    int src_int[] = {1, 2, 3, 4, 5};
    int dest_int[5];
    copy_int_array(dest_int, src_int, 5);
    
    // Double array
    double src_double[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double dest_double[5];
    copy_double_array(dest_double, src_double, 5);
    
    // Char array
    char src_char[] = {'a', 'b', 'c', 'd', 'e'};
    char dest_char[5];
    copy_char_array(dest_char, src_char, 5);
    
    // Print results
    printf("Copied int array: %d %d %d %d %d\n", 
           dest_int[0], dest_int[1], dest_int[2], dest_int[3], dest_int[4]);
    printf("Copied double array: %.1f %.1f %.1f %.1f %.1f\n", 
           dest_double[0], dest_double[1], dest_double[2], dest_double[3], dest_double[4]);
    printf("Copied char array: %c %c %c %c %c\n", 
           dest_char[0], dest_char[1], dest_char[2], dest_char[3], dest_char[4]);
    
    return 0;
}