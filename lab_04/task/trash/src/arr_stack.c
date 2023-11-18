#include "arr_stack.h"
#include "err.h"
#include <stdlib.h>

#define MIN_SIZE 10

struct arr_stack_type
{
    int *data;
    size_t top;
    size_t size;
};

arr_stack_t create(void)
{
    return create_ex(MIN_SIZE);
}

arr_stack_t create_ex(size_t size)
{
    arr_stack_t s = malloc(sizeof(struct arr_stack_type));

    if (s)
    {
        s->data = malloc(size * sizeof(int));

        if (s->data)
        {
            s->size = size;

            make_empty(s);
        }
        else
        {
            free(s);

            s = NULL;
        }
    }

    return s;
}

void destroy(arr_stack_t s)
{
    free(s->data);
    free(s);
}


void make_empty(arr_stack_t s)
{
    s->top = 0;
}


bool is_empty(const arr_stack_t s)
{
    return s->top == 0;
}


bool is_full(const arr_stack_t s)
{
    return s->top == s->size;
}


int push(arr_stack_t s, int i)
{
    if (is_full(s))
        return ERR_RANGE;

    s->data[(s->top)++] = i;

    return 0;
}


int pop(arr_stack_t s, int *i)
{
    assert(s);
	
    if (is_empty(s))
        return ERR_RANGE;

    *i = s->data[--(s->top)];

    return 0;
}



void sort_arr_stack(arr_arr_stack_t input, arr_arr_stack_t output)
{
    Stack temp;
    initStack(&temp);

    while (!isEmpty(input))
    {
        int current = pop(input);

        while (!isEmpty(output) && output->data[output->top] < current)
        {
            push(&temp, pop(output));
        }

        push(output, current);

        while (!isEmpty(&temp))
        {
            push(output, pop(&temp));
        }
    }
}