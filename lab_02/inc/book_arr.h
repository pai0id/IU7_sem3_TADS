#ifndef BOOK_ARR_H
#define BOOK_ARR_H

#include <stdio.h>
#include "book.h"

#define N 700

#include "book_arr.h"
#include "err.h"

int read_arr(FILE *f, struct book_t *books, size_t *pn);

void print_arr_column(FILE *f, struct book_t *books, size_t n);

void print_arr_line(FILE *f, struct book_t *books, size_t n);

void print_arr_id_line(FILE *f, struct book_t *books, size_t n, size_t *id_arr);

void print_arr_by_ids_column(FILE *f, struct book_t *books, size_t n, size_t *id_arr);

void print_arr_by_ids_line(FILE *f, struct book_t *books, size_t n, size_t *id_arr);

void create_id_cnt_pages_arr(size_t n, size_t *id_arr);

int add_book(struct book_t *book, struct book_t *books, size_t *n, size_t *id_arr);

void remove_book(size_t ind, struct book_t *books, size_t *n, size_t *id_arr);

int book_cmp_by_id_page_cnt(size_t l, size_t r, struct book_t *books);

void bubble_sort_book_arr(struct book_t *books, size_t n);

void bubble_sort_book_id_arr(struct book_t *books, size_t n, size_t *id_arr);

void qsort_book_arr(struct book_t *books, int first, int last);

void qsort_book_id_arr(struct book_t *books, int first, int last, size_t *id_arr);

int print_spec(struct book_t *books, size_t n, char *str);

#endif
