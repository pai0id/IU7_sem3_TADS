#ifndef A_QUEUE_H
#define A_QUEUE_H

#include <stdbool.h>
#include <stdio.h>
#include "simulation.h"

typedef struct
{
    types *array;
    size_t size;
    size_t front;
    size_t back;
    size_t capacity;
} arr_queue_type;

typedef arr_queue_type *arr_queue_t;

arr_queue_t arr_queue_create(size_t size);

void arr_queue_destroy(arr_queue_t q);

void arr_queue_make_empty(arr_queue_t q);

bool arr_queue_is_empty(const arr_queue_t q);

int arr_queue_push(arr_queue_t q, types t);

int arr_queue_push_lt_fourth(arr_queue_t q, types t);

int arr_queue_pop(arr_queue_t q, types *t);

#endif
