#pragma once

typedef struct {
    unsigned int rows;
    unsigned int cols;
    double** data;
} Matrix;

Matrix matrix_create(unsigned int rows, unsigned int cols);
void matrix_free(Matrix* matrix);
