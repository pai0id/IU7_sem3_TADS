#include "list_queue.h"
#include "err.h"
#include <stdlib.h>

//-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0

struct node_t *node_create(types t)
{
    struct node_t *tmp = malloc(sizeof(struct node_t));
    if (!tmp)
        return NULL;
    tmp->data = t;
    tmp->next = NULL;
    return tmp;
}

void node_free(struct node_t *node)
{
    free(node);
}

//-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0-0

list_queue_t list_queue_create(void)
{
    list_queue_t tmp = malloc(sizeof(struct list_queue_type));
    if (!tmp)
        return NULL;
    tmp->head = NULL;
    tmp->tail = NULL;
    tmp->size = 0;
    return tmp;
}

void list_queue_destroy(list_queue_t q)
{
    list_queue_make_empty(q);
    free(q);
}

void list_queue_make_empty(list_queue_t q)
{
    types tmp_t;
    while(!list_queue_pop(q, &tmp_t));
}

bool list_queue_is_empty(const list_queue_t q)
{
    return (q->head == NULL) && (q->tail == NULL);
}

int list_queue_push(list_queue_t q, types t)
{
    struct node_t *new_node = node_create(t);
    if (!new_node)
        return ERR_MEM;
    if (!list_queue_is_empty(q))
        q->tail->next = new_node;
    else
        q->head = new_node;
    q->tail = new_node;
    (q->size)++;
    return OK;
}

void *list_queue_push_lt_fourth(list_queue_t q, types t)
{
    struct node_t *new_node = node_create(t);
    if (!new_node)
        return NULL;

    if (list_queue_is_empty(q) || q->size < 4)
    {
        list_queue_push(q, t);
        return q->tail;
    }
    
    struct node_t *temp = q->head;
    for (int i = 1; i < 3; ++i)
    {
        if (temp->next)
            temp = temp->next;
        else
            break;
    }

    new_node->next = temp->next;
    temp->next = new_node;

    if (!new_node->next)
        q->tail = new_node;

    (q->size)++;

    return new_node;
}


int list_queue_pop(list_queue_t q, types *t)
{
    if (list_queue_is_empty(q))
        return ERR_EMPT;
    *t = q->head->data;
    struct node_t *tmp = q->head;
    q->head = q->head->next;
    if (q->head == NULL)
        q->tail = NULL;
    node_free(tmp);
    (q->size)--;
    return OK;
}
