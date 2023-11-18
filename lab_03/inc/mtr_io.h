#ifndef MTR_IO_H
#define MTR_IO_H

#include <stdio.h>
#include <stddef.h>
#include "mtr.h"
#include "err.h"

int matrix_read(FILE *f, mtr_t **mtr);

void matrix_print(FILE *f, mtr_t *mtr);

int vector_read(FILE *f, vector_t **v);

void vector_print(FILE *f, vector_t *v);

#endif
