#include "arr_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "err.h"

arr_queue_t arr_queue_create(size_t size)
{
    arr_queue_t q = (arr_queue_t)malloc(sizeof(arr_queue_type));
    if (q == NULL)
        return NULL;

    q->array = malloc(size * sizeof(types));
    if (q->array == NULL)
    {
        free(q);
        return NULL;
    }

    q->size = 0;
    q->front = 0;
    q->back = 0;
    q->capacity = size;

    return q;
}

void arr_queue_destroy(arr_queue_t q)
{
    if (q == NULL)
        return;

    free(q->array);
    free(q);
}

void arr_queue_make_empty(arr_queue_t q)
{
    if (q == NULL)
        return;

    q->size = 0;
    q->front = 0;
    q->back = 0;
}

bool arr_queue_is_empty(const arr_queue_t q)
{
    return q == NULL || q->size == 0;
}

int arr_queue_push(arr_queue_t q, types t)
{
    if (q == NULL)
        return ERR_EMPT; 

    if (q->size == q->capacity - 1)
    {
        size_t new_capacity = q->capacity * 2;
        types *new_array = realloc(q->array, new_capacity * sizeof(types));
        if (new_array == NULL)
            return ERR_MEM;

        q->array = new_array;
        q->capacity = new_capacity;
    }

    q->array[q->back] = t;
    q->back = (q->back + 1) % q->capacity;
    q->size++;

    return OK;
}

int arr_queue_push_lt_fourth(arr_queue_t q, types t)
{
    if (q == NULL)
        return ERR_EMPT;

    if (q->size <= 3)
    {
        int rc = arr_queue_push(q, t);
        return rc;
    }

    if (q->size == q->capacity - 1)
    {
        size_t new_capacity = q->capacity * 2;
        types *new_array = realloc(q->array, new_capacity * sizeof(types));
        if (new_array == NULL)
            return ERR_MEM;

        q->array = new_array;
        q->capacity = new_capacity;
    }

    size_t insert_index = (q->front + 3) % q->capacity;

    for (size_t i = (q->back + q->capacity - 1) % q->capacity; i != insert_index; i = (i + q->capacity - 1) % q->capacity)
    {
        q->array[(i + 1) % q->capacity] = q->array[i];
    }

    q->array[insert_index] = t;

    q->back = (q->back + 1) % q->capacity;
    q->size++;

    return OK;
}


int arr_queue_pop(arr_queue_t q, types *t)
{
    if (q == NULL)
        return ERR_EMPT;

    if (arr_queue_is_empty(q))
        return ERR_EMPT;

    *t = q->array[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;

    return OK;
}
