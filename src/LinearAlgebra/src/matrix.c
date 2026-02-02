#include "slib/slib.h"
#include "LinearAlgebra/matrix.h"


Matrix matrix_create(unsigned int rows, unsigned int cols) {
    Matrix matrix;
    matrix.rows = rows;
    matrix.cols = cols;
    matrix.data = malloc(rows * cols * sizeof(double));

    if (!matrix.data) {
        matrix.rows = matrix.cols = 0;
    }

    return matrix;
}


void matrix_free(Matrix* matrix) {
    if (!matrix || !matrix -> data) return;

    free(matrix -> data);
    matrix -> data = NULL;
    matrix -> rows = matrix -> cols = 0;
}


Matrix matrix_scalar_multiply(Matrix* matrix, double scalar) {
    Matrix result = matrix_create(matrix -> rows, matrix -> cols);

    for (int i = 0; i < matrix -> rows; i++) {
        for (int j = 0; j < matrix -> cols; j++) {
            unsigned const int index = i * matrix -> cols + j;
            result.data[index] = scalar * matrix -> data[index];
        }
    }

    return result;
}


Matrix matrix_add(Matrix* lhs, Matrix* rhs) {
    Matrix result = matrix_create(lhs -> rows, lhs -> cols);

    for (int i = 0; i < lhs -> rows; i++) {
        for (int j = 0; j < lhs -> cols; j++) {
            unsigned const int index = i * lhs -> cols + j;
            result.data[index] = lhs -> data[index] + rhs -> data[index];
        }
    }

    return result;
}


Matrix matrix_multiply(Matrix* lhs, Matrix* rhs) {
    Matrix result = matrix_create(lhs -> rows, rhs -> cols);

    for (int i = 0; i < lhs -> rows; i++) {
        for (int j = 0; j < rhs -> cols; j++) {
            double sum = 0.0;
            for (int k = 0; k < lhs -> cols; k++) {
                sum += lhs -> data[i * lhs -> cols + k] * rhs -> data[k * rhs -> cols + j];
            }
            result.data[i * lhs -> cols + j] = sum;
        }
    }

    return result;
}


Matrix matrix_transpose(Matrix* matrix) {
    Matrix result = matrix_create(matrix -> cols, matrix -> rows);

    for (int i = 0; i < matrix -> rows; i++) {
        for (int j = 0; j < matrix -> cols; j++) {
            result.data[j * matrix -> cols + i] = matrix -> data[i * matrix -> cols + j];
        }
    }

    return result;
}
