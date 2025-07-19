/*
0_成员函数.md
为struct Matrix添加transpose成员函数，实现矩阵转置
*/
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int rows;
    int cols;
    int** data;
};

// Function to create a matrix
struct Matrix* create_matrix(int rows, int cols) {
    struct Matrix* matrix = (struct Matrix*)malloc(sizeof(struct Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}

// Function to free matrix memory
void free_matrix(struct Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

// Function to print matrix
void print_matrix(struct Matrix* matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

// Global function to transpose matrix
struct Matrix* transpose_matrix(struct Matrix* matrix) {
    struct Matrix* transposed = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            transposed->data[j][i] = matrix->data[i][j];
        }
    }
    return transposed;
}

int main() {
    // Create a 3x2 matrix
    struct Matrix* matrix = create_matrix(3, 2);
    
    // Initialize matrix with values
    matrix->data[0][0] = 1; matrix->data[0][1] = 2;
    matrix->data[1][0] = 3; matrix->data[1][1] = 4;
    matrix->data[2][0] = 5; matrix->data[2][1] = 6;
    
    printf("Original matrix (3x2):\n");
    print_matrix(matrix);
    
    // Transpose the matrix using global function
    struct Matrix* transposed = transpose_matrix(matrix);
    
    printf("\nTransposed matrix (2x3):\n");
    print_matrix(transposed);
    
    // Clean up memory
    free_matrix(matrix);
    free_matrix(transposed);
    
    return 0;
}
