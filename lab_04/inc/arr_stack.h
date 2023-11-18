#ifndef __ARR_STACK_H
#define __ARR_STACK_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct arr_stack_type* arr_stack_t;

bool arr_stack_can_be_merged(arr_stack_t arr_stack1, arr_stack_t arr_stack2);

arr_stack_t arr_stack_create(void);

void arr_stack_cpy(arr_stack_t src, arr_stack_t dst);

void arr_stack_destroy(arr_stack_t s);

void arr_stack_make_empty(arr_stack_t s);

bool arr_stack_is_empty(const arr_stack_t s);

int arr_stack_push(arr_stack_t s, int i);

int arr_stack_pop(arr_stack_t s, int *i);

int arr_stack_top(arr_stack_t s);

void arr_stack_print_stack(arr_stack_t s);

#endif
