#include "mtr_op.h"
#include "mtr_alloc.h"
#include "mtr_io.h"
#include <stdlib.h>
#include <math.h>

double find_match(size_t j, double *A, size_t *IA, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        if (IA[i] == j)
            return A[i];
    }
    return 0;
}

int matrix_mult(mtr_t *mtr, vector_t *v, vector_t **res)
{
    double sum;
    if (mtr->cols != v->rows)
        return ERR_RANGE;

    *res = vector_allocate(mtr->rows, mtr->rows);
    if (*res == NULL)
        return ERR_MEM;

    size_t write = 0;
    for (size_t i = 0; i < mtr->rows; ++i)
    {
        sum = 0;
        for (size_t j = mtr->IA[i]; j < mtr->IA[i + 1]; ++j)
        {
            sum += mtr->A[j] * find_match(mtr->JA[j], v->A, v->IA, v->nz);
        }
        
        if (fabs(sum) > EPS)
        {
            (*res)->A[write] = sum;
            (*res)->IA[write] = i; // Индекс строки вектора остается тем же
            write++;
        }
    }
    (*res)->nz = write;

    return OK;
}
