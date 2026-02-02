#pragma once

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double* data;
} Matrix;

Matrix matrix_create(unsigned int rows, unsigned int cols);
void matrix_free(Matrix* matrix);

Matrix matrix_add(Matrix* lhs, Matrix* rhs);
Matrix matrix_multiply(Matrix* lhs, Matrix* rhs);
Matrix matrix_transpose(Matrix* matrix);
