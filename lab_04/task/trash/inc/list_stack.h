#ifndef __LIST_STACK_H
#define __LIST_STACK_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct node* list_stack_t;

list_stack_t list_stack_create(void);

list_stack_t list_stack_create_ex(size_t size);

void list_stack_destroy(list_stack_t s);

void list_stack_make_empty(list_stack_t s);

bool list_stack_is_empty(const list_stack_t s);

bool list_stack_is_full(const list_stack_t s);

int list_stack_push(list_stack_t s, int i);

int list_stack_pop(list_stack_t s, int *i);

void list_stack_merge_sort(list_stack_t input_stack1, list_stack_t input_stack2, list_stack_t output_stack);

#endif
