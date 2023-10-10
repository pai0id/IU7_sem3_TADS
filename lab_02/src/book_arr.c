#include "book_arr.h"
#include "err.h"
#include <string.h>

int read_arr(FILE *f, struct book_t *books, size_t *pn)
{
    struct book_t curr;
    size_t i = 0;
    int rc = OK;

    while (!rc)
    {
        rc = read_book(f, &curr);
        if (!rc)
        {
            if (i < N)
            {
                books[i++] = curr;
            }
            else
                rc = ERR_OVERFLOW;
        }
    }
    *pn = i;
    if (rc && feof(f))
        rc = OK;
    return rc;
}

void print_arr_column(FILE *f, struct book_t *books, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        print_book_column(f, &books[i]);
}

void print_arr_line(FILE *f, struct book_t *books, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        print_book_line(f, &books[i]);
}

void print_arr_id_line(FILE *f, struct book_t *books, size_t n, size_t *id_arr)
{
    for (size_t i = 0; i < n; ++i)
        fprintf(f, "%lu - %lu - %d\n", i, id_arr[i], books[id_arr[i]].page_cnt);
}

void print_arr_by_ids_column(FILE *f, struct book_t *books, size_t n, size_t *id_arr)
{
    for (size_t i = 0; i < n; ++i)
        print_book_column(f, &books[id_arr[i]]);
}

void print_arr_by_ids_line(FILE *f, struct book_t *books, size_t n, size_t *id_arr)
{
    for (size_t i = 0; i < n; ++i)
        print_book_line(f, &books[id_arr[i]]);
}

void create_id_cnt_pages_arr(size_t n, size_t *id_arr)
{
    for (size_t i = 0; i < n; ++i)
        id_arr[i] = i;
}

int add_book(struct book_t *book, struct book_t *books, size_t *n, size_t *id_arr)
{
    if (*n + 1 > N)
        return ERR_OVERFLOW;
    books[*n] = *book;
    if (id_arr != NULL)
        id_arr[*n] = *n;
    (*n)++;
    return OK;
}

void remove_book(size_t ind, struct book_t *books, size_t *n, size_t *id_arr)
{
    if (ind >= *n)
        ind = *n - 1;
    memmove(&books[ind], &books[ind + 1], (*n - ind) * sizeof(struct book_t));
    if (id_arr != NULL)
        memmove(&id_arr[ind], &id_arr[ind + 1], (*n - ind) * sizeof(size_t));
    (*n)--;
}

int book_cmp_by_id_page_cnt(size_t l, size_t r, struct book_t *books)
{
    return (books[l].page_cnt - books[r].page_cnt);
}


void bubble_sort_book_arr(struct book_t *books, size_t n)
{
    struct book_t tmp;
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (book_cmp_by_page_cnt(&books[i], &books[j]) < 0)
            {
                tmp = books[i];
                books[i] = books[j];
                books[j] = tmp;
            }
        }
    }
}

void bubble_sort_book_id_arr(struct book_t *books, size_t n, size_t *id_arr)
{
    size_t tmp;
    for (int i = n - 1; i >= 0; --i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (book_cmp_by_id_page_cnt(id_arr[i], id_arr[j], books) < 0)
            {
                tmp = id_arr[i];
                id_arr[i] = id_arr[j];
                id_arr[j] = tmp;
            }
        }
    }
}

// int book_arr_partion(struct book_t *books, int low, int high)
// {
//     struct book_t *pivot = &books[high];
//     struct book_t tmp;
//     int i = low - 1;

//     for (int j = low; j < high; j++)
//     {
//         if (book_cmp_by_page_cnt(&books[j], pivot) <= 0)
//         {
//             i++;
//             tmp = books[j];
//             books[j] = books[i];
//             books[i] = tmp;
//         }
//     }

//     tmp = books[high];
//     books[high] = books[i + 1];
//     books[i + 1] = tmp;
//     return (i + 1);
// }

// void qsort_book_arr(struct book_t *books, int low, int high)
// {
//     if (low < high)
//     {
//         int mid = book_arr_partion(books, low, high);
//         qsort_book_arr(books, low, mid - 1);
//         qsort_book_arr(books, mid + 1, high);
//     }
// }

void qsort_book_arr(struct book_t *books, int first, int last)
{
    struct book_t tmp;
    if (first < last)
    {
        int left = first, right = last;
        struct book_t middle = books[(left + right) / 2];
        do
        {
            while (book_cmp_by_page_cnt(&books[left], &middle) < 0)
                left++;
            while (book_cmp_by_page_cnt(&books[right], &middle) > 0)
                right--;
            if (left <= right)
            {
                tmp = books[left];
                books[left] = books[right];
                books[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qsort_book_arr(books, first, right);
        qsort_book_arr(books, left, last);
    }
}

// int book_arr_id_partion(struct book_t *books, size_t *id_arr, int low, int high)
// {
//     size_t pivot = id_arr[high];
//     size_t tmp;
//     int i = low - 1;

//     for (int j = low; j < high; j++)
//     {
//         if (book_cmp_by_id_page_cnt(id_arr[j], pivot, books) <= 0)
//         {
//             i++;
//             tmp = id_arr[j];
//             id_arr[j] = id_arr[i];
//             id_arr[i] = tmp;
//         }
//     }
//     tmp = id_arr[high];
//     id_arr[high] = id_arr[i + 1];
//     id_arr[i + 1] = tmp;
//     return (i + 1);
// }

// void qsort_book_id_arr(struct book_t *books, int low, int high, size_t *id_arr)
// {
//     if (low < high)
//     {
//         int mid = book_arr_id_partion(books, id_arr, low, high);
//         qsort_book_id_arr(books, low, mid - 1, id_arr);
//         qsort_book_id_arr(books, mid + 1, high, id_arr);
//     }
// }

void qsort_book_id_arr(struct book_t *books, int first, int last, size_t *id_arr)
{
    size_t tmp;
    if (first < last)
    {
        int left = first, right = last;
        size_t middle = id_arr[(left + right) / 2];
        do
        {
            while (book_cmp_by_id_page_cnt(id_arr[left], middle, books) < 0)
                left++;
            while (book_cmp_by_id_page_cnt(id_arr[right], middle, books) > 0)
                right--;
            if (left <= right)
            {
                tmp = id_arr[left];
                id_arr[left] = id_arr[right];
                id_arr[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        qsort_book_id_arr(books, first, right, id_arr);
        qsort_book_id_arr(books, left, last, id_arr);
    }
}

int print_spec(struct book_t *books, size_t n, char *str)
{
    int cnt = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (strcmp(books[i].surname, str) == 0 && books[i].type == FICTION && books[i].chars.fict.type == NOVEL)
        {
            print_book_line(stdout, &books[i]);
            cnt++;
        }
    }
    if (!cnt)
        return ERR_NO_SPEC;
    return OK;
}
