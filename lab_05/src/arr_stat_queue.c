#include "arr_stat_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "err.h"

arr_stat_queue_t arr_stat_queue_create()
{
    arr_stat_queue_t q = (arr_stat_queue_t)malloc(sizeof(arr_stat_queue_type));
    if (q == NULL)
        return NULL;

    q->size = 0;
    q->front = 0;
    q->back = 0;

    return q;
}

void arr_stat_queue_destroy(arr_stat_queue_t q)
{
    if (q == NULL)
        return;

    free(q);
}

void arr_stat_queue_make_empty(arr_stat_queue_t q)
{
    if (q == NULL)
        return;

    q->size = 0;
    q->front = 0;
    q->back = 0;
}

bool arr_stat_queue_is_empty(const arr_stat_queue_t q)
{
    return q == NULL || q->size == 0;
}

int arr_stat_queue_push(arr_stat_queue_t q, types t)
{
    if (q == NULL)
        return ERR_EMPT; 

    if (q->size + 1 >= N)
        return ERR_RANGE;

    q->array[q->back] = t;
    q->back = (q->back + 1) % N;
    q->size++;

    return OK;
}

int arr_stat_queue_push_lt_fourth(arr_stat_queue_t q, types t)
{
    if (q == NULL)
        return ERR_EMPT;

    if (q->size + 1 >= N)
        return ERR_RANGE;

    if (q->size <= 3)
        return arr_stat_queue_push(q, t);

    size_t insert_index = (q->front + 3) % N;

    for (size_t i = (q->back + N - 1) % N; i != insert_index; i = (i + N - 1) % N)
        q->array[(i + 1) % N] = q->array[i];

    q->array[insert_index] = t;

    q->back = (q->back + 1) % N;
    q->size++;

    return OK;
}


int arr_stat_queue_pop(arr_stat_queue_t q, types *t)
{
    if (q == NULL)
        return ERR_EMPT;

    if (arr_stat_queue_is_empty(q))
        return ERR_EMPT;

    *t = q->array[q->front];
    q->front = (q->front + 1) % N;
    q->size--;

    return OK;
}
