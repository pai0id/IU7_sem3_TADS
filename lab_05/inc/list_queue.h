#ifndef L_QUEUE_H
#define L_QUEUE_H

#include <stdbool.h>
#include "simulation.h"

struct node_t
{
    types data;
    struct node_t *next;
};

struct list_queue_type
{
    struct node_t *head;
    struct node_t *tail;
    size_t size;
};

typedef struct list_queue_type *list_queue_t;

struct node_t *node_create(types t);

void node_free(struct node_t *node);

list_queue_t list_queue_create(void);

void list_queue_destroy(list_queue_t q);

void list_queue_make_empty(list_queue_t q);

bool list_queue_is_empty(const list_queue_t q);

int list_queue_push(list_queue_t q, types t);

void *list_queue_push_lt_fourth(list_queue_t q, types t);

int list_queue_pop(list_queue_t q, types *t);

#endif
