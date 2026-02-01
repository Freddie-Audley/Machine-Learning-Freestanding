#include "slib/slib.h"
#include "LinearAlgebra/matrix.h"

Matrix matrix_create(unsigned int rows, unsigned int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = malloc(rows * sizeof(double*));

    if (!matrix.data) {
        matrix.rows = matrix.cols = 0;
        return matrix;
    }

    for (int i = 0; i < rows; i++) {
        matrix.data[i] = malloc(cols * sizeof(double));

        if (!matrix.data[i]) {
            for (int j = 0; j < i; j++) {
                free(matrix.data[j]);
            }
            free(matrix.data);
            matrix.data = NULL;
            matrix.rows = matrix.cols = 0;
            return matrix;
        }
    }

    return matrix;
}


void matrix_free(Matrix* matrix) {
    if (!matrix || !matrix -> data) return;

    for (int i = 0; i < matrix -> rows; i++) {
        free(matrix -> data[i]);
    }

    free(matrix -> data);
    matrix -> data = NULL;
    matrix -> rows = matrix -> cols = 0;
}
