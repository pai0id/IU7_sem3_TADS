#ifndef __STACK_OP_H
#define __STACK_OP_H

#include "arr_stack.h"
#include "list_stack.h"

void arr_stack_sort(arr_stack_t s);

void arr_stack_merge_sort(arr_stack_t input_stack1, arr_stack_t input_stack2, arr_stack_t output_stack);

void list_stack_sort(list_stack_t *s, freed_stack_t freed_stack);

void list_stack_merge_sort(list_stack_t *list_stack1, list_stack_t *list_stack2, list_stack_t *sorted_list_stack, freed_stack_t freed_stack);

#endif
