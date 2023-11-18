#ifndef __LIST_STACK_H
#define __LIST_STACK_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct node* list_stack_t;

typedef struct freed_stack_type* freed_stack_t;

freed_stack_t init_freed_stack(size_t capacity);

void add_freed_address(freed_stack_t freed_stack, list_stack_t address);

void destroy_freed_stack(freed_stack_t freed_stack);

void print_freed_stack(freed_stack_t freed_stack);

//------------------------

void list_stack_cpy(list_stack_t src, list_stack_t *dst, freed_stack_t f);

list_stack_t list_stack_create_node(int data, list_stack_t next, freed_stack_t freed_stack);

list_stack_t list_stack_destroy_node(list_stack_t node, freed_stack_t freed_stack);

void list_stack_destroy(list_stack_t node, freed_stack_t freed_stack);

list_stack_t list_stack_push(list_stack_t top, int data, freed_stack_t freed_stack);

int list_stack_pop(list_stack_t *top, int* data, freed_stack_t freed_stack);

int list_stack_top(list_stack_t top);

bool list_stack_is_empty(const list_stack_t top);

void list_stack_print_stack(list_stack_t top);

// void list_stack_merge_sort(list_stack_t *list_stack1, list_stack_t *list_stack2, list_stack_t *sorted_list_stack, freed_stack_t fread_stack);

#endif
