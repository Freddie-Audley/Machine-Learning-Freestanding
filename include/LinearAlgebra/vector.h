#pragma once

typedef struct {
    unsigned int size;
    double* data;
} Vector;

Vector vector_create(unsigned int size);
void vector_free(Vector* vector);

Vector vector_scalar_multiply(Vector* vector, double scalar);
Vector vector_add(Vector* lhs, Vector* rhs);
