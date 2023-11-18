#ifndef RESEARCH_H
#define RESEARCH_H

#include "stdio.h"
#include "mtr.h"
#include "err.h"

void old_matrix_free(double **data, size_t n);

double **old_matrix_allocate(size_t n, size_t m);

void old_matrix_fill_null(double **data, size_t n, size_t m);

int old_matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m);

double **transform_mtr(mtr_t *mtr);

double **transform_vector(vector_t *v);

void old_matrix_print_coord(FILE *f, double **data, size_t n, size_t m, size_t n_el);

//___________________________________________________________________________________

// Функция для вычисления среднего значения
double calc_mean(const long long data[], size_t length);

// Функция для вычисления стандартного отклонения
double calc_stdev(const long long data[], size_t length, double avr);

// Функция для вычисления относительной стандартной ошибки (RSE)
double calc_rse(size_t length, double avr, double stdev);

double run_tests_sparse(mtr_t *mtr, vector_t *v);

double run_tests_old(double **mtr, size_t n_mtr, size_t m_mtr, double **v, size_t n_v, size_t m_v);

int cmp_methods(mtr_t *mtr, vector_t *v);

#endif
