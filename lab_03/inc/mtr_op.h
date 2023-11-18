#ifndef MTR_OP_H
#define MTR_OP_H

#include <stddef.h>
#include "mtr.h"
#include "err.h"

int matrix_mult(mtr_t *mtr, vector_t *v, vector_t **res);

#endif
