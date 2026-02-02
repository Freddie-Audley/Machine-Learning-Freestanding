#include "slib/slib.h"
#include "LinearAlgebra/vector.h"


Vector vector_create(unsigned int size) {
    Vector vector;
    vector.size = size;
    vector.data = malloc(sizeof(double) * size);
    return vector;
}


void vector_free(Vector* vector) {
    if (!vector || !vector -> data) return;
    free(vector -> data);
    vector -> data = NULL;
    vector -> size = 0;
}


Vector vector_scalar_multiply(Vector* vector, double scalar) {
    Vector result = vector_create(vector -> size);

    for (int i = 0; i < vector -> size; i++) {
        result.data[i] = vector -> data[i] * scalar;
    }

    return result;
}


Vector vector_add(Vector* lhs, Vector* rhs) {
    Vector result = vector_create(lhs -> size);

    for (int i = 0; i < lhs -> size; i++) {
        result.data[i] = lhs -> data[i] + rhs -> data[i];
    }

    return result;
}


Vector vector_dot(Vector* lhs, Vector* rhs) {
    Vector result = vector_create(lhs -> size);

    for (int i = 0; i < lhs -> size; i++) {
        result.data[i] = lhs -> data[i] * rhs -> data[i];
    }

    return result;
}


double vector_norm(Vector* vector) {
    double result = 0.0;

    for (int i = 0; i < vector -> size; i++) {
        result += vector -> data[i] * vector -> data[i];
    }

    return sqrt(result);
}
