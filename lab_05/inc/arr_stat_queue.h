#ifndef A_QUEUE_H
#define A_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include "simulation.h"

#define N 10000

typedef struct
{
    types array[N];
    size_t size;
    size_t front;
    size_t back;
} arr_stat_queue_type;

typedef arr_stat_queue_type *arr_stat_queue_t;

arr_stat_queue_t arr_stat_queue_create();

void arr_stat_queue_destroy(arr_stat_queue_t q);

void arr_stat_queue_make_empty(arr_stat_queue_t q);

bool arr_stat_queue_is_empty(const arr_stat_queue_t q);

int arr_stat_queue_push(arr_stat_queue_t q, types t);

int arr_stat_queue_push_lt_fourth(arr_stat_queue_t q, types t);

int arr_stat_queue_pop(arr_stat_queue_t q, types *t);

#endif
