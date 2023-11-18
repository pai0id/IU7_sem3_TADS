#include "mtr_alloc.h"
#include <stdlib.h>

void matrix_free(mtr_t *mtr)
{
    free(mtr->A);
    free(mtr->JA);
    free(mtr->IA);
    free(mtr);
}

mtr_t* matrix_allocate(size_t rows, size_t cols, size_t nz)
{
    mtr_t* matrix = (mtr_t*)malloc(sizeof(mtr_t));

    if (matrix == NULL)
        return NULL; // Не удалось выделить память под структуру mtr_t

    matrix->A = (double*)malloc(nz * sizeof(double));
    if (matrix->A == NULL)
    {
        free(matrix);
        return NULL; // Не удалось выделить память под элементы матрицы
    }

    matrix->JA = (size_t*)malloc(nz * sizeof(size_t));
    if (matrix->JA == NULL)
    {
        free(matrix->A);
        free(matrix);
        return NULL; // Не удалось выделить память под элементы матрицы
    }

    matrix->IA = (size_t*)malloc((rows + 1) * sizeof(size_t));
    if (matrix->IA == NULL)
    {
        free(matrix->A);
        free(matrix->JA);
        free(matrix);
        return NULL; // Не удалось выделить память под элементы матрицы
    }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->nz = nz;

    return matrix;
}


void vector_free(vector_t *v)
{
    free(v->A);
    free(v->IA);
    free(v);
}

vector_t* vector_allocate(size_t rows, size_t nz)
{
    vector_t* vector = (vector_t*)malloc(sizeof(vector_t));

    if (vector == NULL)
        return NULL; // Не удалось выделить память под структуру vector_t

    vector->A = (double*)malloc(nz * sizeof(double));
    if (vector->A == NULL)
    {
        free(vector);
        return NULL; // Не удалось выделить память под элементы вектора
    }

    vector->IA = (size_t*)malloc(nz * sizeof(size_t));
    if (vector->IA == NULL)
    {
        free(vector->A);
        free(vector);
        return NULL; // Не удалось выделить память под элементы вектора
    }

    vector->rows = rows;
    vector->nz = nz;

    return vector;
}

