#ifndef RESEARCH_H
#define RESEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include "book.h"
#include "book_arr.h"

#define MAX_NUM_TESTS 800

double run_tests_bubble(struct book_t *pbooks, size_t n);

double run_tests_bubble_id(struct book_t *books, size_t n, size_t *p_id_arr);

double run_tests_qsort(struct book_t *pbooks, size_t n);

double run_tests_qsort_id(struct book_t *books, size_t n, size_t *p_id_arr);

double run_tests_get_num_by_id(struct book_t *books, size_t n, size_t *p_id_arr);

void run_tests(struct book_t *books, size_t n, size_t *id_arr);

double calc_mean(const long long data[], size_t length);

double calc_stdev(const long long data[], size_t length, double avr);

double calc_rse(size_t length, double avr, double stdev);

void input_sorted(int arr[], size_t a_size);

void input_rand(int arr[], size_t a_size);

#endif
