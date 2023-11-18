#include "arr_stack.h"
#include "err.h"
#include <stdlib.h>

#define SIZE 10000

struct arr_stack_type
{
    int data[SIZE];
    size_t top;
};

bool arr_stack_can_be_merged(arr_stack_t arr_stack1, arr_stack_t arr_stack2)
{
    if (arr_stack1->top + arr_stack2->top + 2 > SIZE)
        return false;
    return true;
}

void arr_stack_cpy(arr_stack_t src, arr_stack_t dst)
{
    dst->top = src->top;
    for (size_t i = 0; i < src->top; ++i)
        (dst->data)[i] = (src->data)[i];
}

arr_stack_t arr_stack_create(void)
{
    arr_stack_t s = malloc(sizeof(struct arr_stack_type));
    arr_stack_make_empty(s);
    return s;
}

void arr_stack_destroy(arr_stack_t s)
{
    free(s);
}

void arr_stack_make_empty(arr_stack_t s)
{
    s->top = 0;
}

bool arr_stack_is_empty(const arr_stack_t s)
{
    return s->top == 0;
}

int arr_stack_push(arr_stack_t s, int i)
{
    if (s->top + 1 >= SIZE)
        return ERR_RANGE;

    s->data[(s->top)++] = i;

    return OK;
}

int arr_stack_pop(arr_stack_t s, int *i)
{
    if (arr_stack_is_empty(s))
        return ERR_RANGE;

    *i = s->data[--(s->top)];

    return OK;
}

int arr_stack_top(arr_stack_t s)
{
    if (s->top != 0)
        return (s->data)[s->top - 1];
    return 0;
}

// void arr_stack_sort(arr_stack_t s)
// {
//     int i, j, temp;
//     size_t n = s->top;

//     for (i = 0; i < n - 1; i++)
//     {
//         for (j = 0; j < n - i - 1; j++)
//         {
//             if (s->data[j] < s->data[j + 1])
//             {
//                 temp = s->data[j];
//                 s->data[j] = s->data[j + 1];
//                 s->data[j + 1] = temp;
//             }
//         }
//     }
// }

// void arr_stack_merge_sort(arr_stack_t input_stack1, arr_stack_t input_stack2, arr_stack_t output_stack)
// {
//     int rc;
//     int x1, x2;
//     arr_stack_sort(input_stack1);
//     arr_stack_sort(input_stack2);

//     while (!arr_stack_is_empty(input_stack1) && !arr_stack_is_empty(input_stack2))
//     {
//         arr_stack_pop(input_stack1, &x1);
//         arr_stack_pop(input_stack2, &x2);
//         if (x1 < x2)
//         {
//             arr_stack_push(output_stack, x1);
//             arr_stack_push(input_stack2, x2);
//         }
//         else
//         {
//             arr_stack_push(output_stack, x2);
//             arr_stack_push(input_stack1, x1);
//         }
//     }
//     while (!arr_stack_is_empty(input_stack1))
//     {
//         arr_stack_pop(input_stack1, &x1);
//         arr_stack_push(output_stack, x1);
//     }
//     while (!arr_stack_is_empty(input_stack2))
//     {
//         arr_stack_pop(input_stack2, &x2);
//         arr_stack_push(output_stack, x2);
//     }
// }

void arr_stack_print_stack(arr_stack_t s)
{
    if (arr_stack_is_empty(s))
    {
        printf("Стек пуст.\n");
        return;
    }

    printf("Содержимое стека:\n");

    for (int i = ((int)s->top) - 1; i >= 0; i--)
    {
        printf("%d\n", s->data[i]);
    }
    printf("\n");
}
