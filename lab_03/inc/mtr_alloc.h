#ifndef MTR_ALLOC_H
#define MTR_ALLOC_H

#include <stddef.h>
#include "mtr.h"
#include "err.h"

void matrix_free(mtr_t *mtr);

mtr_t* matrix_allocate(size_t rows, size_t cols, size_t nz);

void vector_free(vector_t *v);

vector_t* vector_allocate(size_t rows, size_t nz);

#endif
