/*
0_成员函数.md
为struct Matrix添加transpose成员函数，矩阵转置
*/
#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int rows;
    int cols;
    int **data;
};

struct Matrix* create_matrix(int rows, int cols) {
    struct Matrix *matrix = malloc(sizeof(struct Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix->data[i] = malloc(cols * sizeof(int));
    }
    return matrix;
}

void free_matrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        free(matrix->data[i]);
    }
    free(matrix->data);
    free(matrix);
}

struct Matrix* transpose_matrix(struct Matrix *matrix) {
    struct Matrix *result = create_matrix(matrix->cols, matrix->rows);
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            result->data[j][i] = matrix->data[i][j];
        }
    }
    return result;
}

void print_matrix(struct Matrix *matrix) {
    for (int i = 0; i < matrix->rows; i++) {
        for (int j = 0; j < matrix->cols; j++) {
            printf("%d ", matrix->data[i][j]);
        }
        printf("\n");
    }
}

int main() {
    struct Matrix *matrix = create_matrix(2, 3);
    
    matrix->data[0][0] = 1; matrix->data[0][1] = 2; matrix->data[0][2] = 3;
    matrix->data[1][0] = 4; matrix->data[1][1] = 5; matrix->data[1][2] = 6;
    
    printf("Original matrix:\n");
    print_matrix(matrix);
    
    struct Matrix *transposed = transpose_matrix(matrix);
    printf("Transposed matrix:\n");
    print_matrix(transposed);
    
    free_matrix(matrix);
    free_matrix(transposed);
    
    return 0;
}