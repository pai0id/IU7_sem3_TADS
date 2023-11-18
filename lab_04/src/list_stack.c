#include "list_stack.h"
#include "err.h"
#include <stdlib.h>

// Определение структуры узла
struct node
{
    int data;
    struct node* next;
};

void list_stack_cpy(list_stack_t src, list_stack_t *dst, freed_stack_t f)
{
    list_stack_t tmp = NULL;
    freed_stack_t fr = init_freed_stack(100);
    for (list_stack_t curr = src; curr != NULL; curr = curr->next)
        tmp = list_stack_push(tmp, curr->data, f);
    for (list_stack_t curr = tmp; curr != NULL; curr = curr->next)
        *dst = list_stack_push(*dst, curr->data, f);
    list_stack_destroy(tmp, fr);
    destroy_freed_stack(fr);
}

//----------------------------------

struct freed_stack_type
{
    list_stack_t* arr;
    size_t size;
    size_t capacity;
};

freed_stack_t init_freed_stack(size_t capacity)
{
    freed_stack_t s = malloc(sizeof(struct freed_stack_type));
    s->arr = malloc(sizeof(list_stack_t) * capacity);
    s->capacity = capacity;
    s->size = 0;
    return s;
}

void add_freed_address(freed_stack_t freed_stack, list_stack_t address)
{
    if (address != NULL)
    {
        if (++(freed_stack->size) >= freed_stack->capacity)
        {
            freed_stack->arr = realloc(freed_stack->arr, sizeof(list_stack_t) * freed_stack->capacity * 2);
            freed_stack->capacity *= 2;
        }
        (freed_stack->arr)[freed_stack->size - 1] = address;
    }
}

void del_copy(freed_stack_t freed, list_stack_t addres)
{
    size_t n_s = 0;

    for (size_t i = 0; i < freed->size; ++i)
        if (freed->arr[i] != addres)
            freed->arr[n_s++] = freed->arr[i];

    freed->size = n_s;
}

void destroy_freed_stack(freed_stack_t freed_stack)
{
    free(freed_stack->arr);
    free(freed_stack);
}

void print_freed_stack(freed_stack_t freed_stack)
{
    if (freed_stack->size == 0)
        printf("Пуст\n");
    else
        for (int i = ((int) freed_stack->size) - 1; i >= 0; --i)
            printf("%p\n", (void*)(freed_stack->arr)[i]);
}

//-----------------------------------

list_stack_t list_stack_create_node(int data, list_stack_t next, freed_stack_t freed_stack)
{
    list_stack_t node = malloc(sizeof(struct node));
    if (!node)
        return NULL;
    node->data = data;
    if (next != NULL)
        node->next = next;
    else
        node->next = NULL;
    // if (freed_stack != NULL)
    //     del_copy(freed_stack, node);
    return node;
}

list_stack_t list_stack_destroy_node(list_stack_t node, freed_stack_t freed_stack)
{
    list_stack_t tmp = node->next;
    add_freed_address(freed_stack, node);
    free(node);
    return tmp;
}

void list_stack_destroy(list_stack_t node, freed_stack_t freed_stack)
{
    while (node)
        node = list_stack_destroy_node(node, freed_stack);
    
}

list_stack_t list_stack_push(list_stack_t top, int data, freed_stack_t freed_stack)
{
    list_stack_t tmp = list_stack_create_node(data, top, freed_stack);
    if (!tmp)
        return top;
    return tmp;
}

int list_stack_pop(list_stack_t *top, int* data, freed_stack_t freed_stack)
{
    if (list_stack_is_empty(*top))
        return ERR_IO;
    *data = (*top)->data;
    *top = list_stack_destroy_node(*top, freed_stack);
    return OK;
}

int list_stack_top(list_stack_t top)
{
    if (top != NULL)
        return top->data;
    return 0;
}

bool list_stack_is_empty(const list_stack_t top)
{
    if (top == NULL)
        return true;
    return false;
}

void list_stack_print_stack(const list_stack_t top)
{
    if (list_stack_is_empty(top))
    {
        printf("Стек пуст.\n");
        return;
    }

    printf("Содержимое стека(число - адрес):\n");

    for (list_stack_t curr = top; curr != NULL; curr = curr->next)
    {
        printf("%d - %p\n", curr->data, (void*)curr);
    }
    printf("\n");
}

// void list_stack_merge_sort(list_stack_t *list_stack1, list_stack_t *list_stack2, list_stack_t *sorted_list_stack, freed_stack_t fread_stack)
// {

// }
