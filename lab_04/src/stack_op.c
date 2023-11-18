#include "stack_op.h"

void arr_stack_sort(arr_stack_t s)
{
    arr_stack_t tmp = arr_stack_create();
    int x, y;

    while (!arr_stack_is_empty(s))
    {
        arr_stack_pop(s, &x);

        while (!arr_stack_is_empty(tmp) && arr_stack_top(tmp) > x)
        {
            arr_stack_pop(tmp, &y);
            arr_stack_push(s, y);
        }

        arr_stack_push(tmp, x);
    }

    while (!arr_stack_is_empty(tmp))
    {
        arr_stack_pop(tmp, &y);
        arr_stack_push(s, y);
    }

    arr_stack_destroy(tmp);
}

void arr_stack_merge_sort(arr_stack_t input_stack1, arr_stack_t input_stack2, arr_stack_t output_stack)
{
    int x1, x2;
    arr_stack_sort(input_stack1);
    arr_stack_sort(input_stack2);

    while (!arr_stack_is_empty(input_stack1) && !arr_stack_is_empty(input_stack2))
    {
        arr_stack_pop(input_stack1, &x1);
        arr_stack_pop(input_stack2, &x2);
        if (x1 < x2)
        {
            arr_stack_push(output_stack, x1);
            arr_stack_push(input_stack2, x2);
        }
        else
        {
            arr_stack_push(output_stack, x2);
            arr_stack_push(input_stack1, x1);
        }
    }
    while (!arr_stack_is_empty(input_stack1))
    {
        arr_stack_pop(input_stack1, &x1);
        arr_stack_push(output_stack, x1);
    }
    while (!arr_stack_is_empty(input_stack2))
    {
        arr_stack_pop(input_stack2, &x2);
        arr_stack_push(output_stack, x2);
    }
}

void list_stack_sort(list_stack_t *s, freed_stack_t freed_stack)
{
    list_stack_t tmp = NULL;
    int x, y;

    while (!list_stack_is_empty(*s))
    {
        list_stack_pop(s, &x, freed_stack);

        while (!list_stack_is_empty(tmp) && list_stack_top(tmp) > x)
        {
            list_stack_pop(&tmp, &y, freed_stack);
            *s = list_stack_push(*s, y, freed_stack);
        }

        tmp = list_stack_push(tmp, x, freed_stack);
    }

    while (!list_stack_is_empty(tmp))
    {
        list_stack_pop(&tmp, &y, freed_stack);
        *s = list_stack_push(*s, y, freed_stack);
    }

    list_stack_destroy(tmp, freed_stack);
}

void list_stack_merge_sort(list_stack_t *list_stack1, list_stack_t *list_stack2, list_stack_t *sorted_list_stack, freed_stack_t freed_stack)
{
    int x1, x2;
    list_stack_sort(list_stack1, freed_stack);
    list_stack_sort(list_stack2, freed_stack);

    while (!list_stack_is_empty(*list_stack1) && !list_stack_is_empty(*list_stack2))
    {
        list_stack_pop(list_stack1, &x1, freed_stack);
        list_stack_pop(list_stack2, &x2, freed_stack);
        if (x1 < x2)
        {
            *sorted_list_stack = list_stack_push(*sorted_list_stack, x1, freed_stack);
            *list_stack2 = list_stack_push(*list_stack2, x2, freed_stack);
        }
        else
        {
            *sorted_list_stack = list_stack_push(*sorted_list_stack, x2, freed_stack);
            *list_stack1 = list_stack_push(*list_stack1, x1, freed_stack);
        }
    }
    while (!list_stack_is_empty(*list_stack1))
    {
        list_stack_pop(list_stack1, &x1, freed_stack);
        *sorted_list_stack = list_stack_push(*sorted_list_stack, x1, freed_stack);
    }
    while (!list_stack_is_empty(*list_stack2))
    {
        list_stack_pop(list_stack2, &x2, freed_stack);
        *sorted_list_stack = list_stack_push(*sorted_list_stack, x2, freed_stack);
    }
}
