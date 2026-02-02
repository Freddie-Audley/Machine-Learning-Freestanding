#include "LinearAlgebra/LinearAlgebra.h"


Vector apply_matrix(Matrix* matrix, Vector* vector) {
    Vector result = vector_create(vector -> size);

    for (int i = 0; i < matrix -> rows; i++) {
        double sum = 0.0;

        for (int j = 0; j < matrix -> cols; j++) {
            sum += matrix -> data[i * matrix -> cols + j] * vector -> data[j];
        }

        result.data[i] = sum;
    }

    return result;
}
