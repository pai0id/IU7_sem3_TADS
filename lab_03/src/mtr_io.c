#include "mtr_io.h"
#include "mtr_alloc.h"
#include <stdlib.h>
#include <math.h>

int matrix_read(FILE *f, mtr_t **mtr)
{
    size_t rows, cols, nz;
    if (f == stdin)
    {
        printf("Введите n: ");
        if (fscanf(f, "%lu", &rows) != 1)
            return ERR_IO;
        printf("Введите m: ");
        if (fscanf(f, "%lu", &cols) != 1)
            return ERR_IO;
        printf("Введите количество ненулевых элементов: ");
        if (fscanf(f, "%lu", &nz) != 1)
            return ERR_IO;
    }
    else
    {
        if (fscanf(f, "%lu %lu %lu\n", &rows, &cols, &nz) != 3)
            return ERR_IO;
    }

    (*mtr) = matrix_allocate(rows, cols, nz);

    if ((*mtr) == NULL)
        return ERR_MEM;
    
    size_t current_row = 0; // Текущая строка
    (*mtr)->IA[0] = 0;  // Первая строка начинается с индекса 0

    size_t row, col, prev_row = 0, prev_col = 0;
    double value;
    for (size_t i = 0; i < nz; ++i)
    {
        if (f == stdin)
        {
            printf("Элемент №%lu\n", i + 1);
            printf("Введите i: ");
            if (fscanf(f, "%lu", &row) != 1)
            {
                matrix_free((*mtr));
                return ERR_IO;
            }
            printf("Введите j: ");
            if (fscanf(f, "%lu", &col) != 1)
            {
                matrix_free((*mtr));
                return ERR_IO;
            }
            printf("Введите элемент: ");
            if (fscanf(f, "%lf", &value) != 1)
            {
                matrix_free((*mtr));
                return ERR_IO;
            }
        }
        else
        {
            if (fscanf(f, "%lu %lu %lf\n", &row, &col, &value) != 3)
            {
                matrix_free((*mtr));
                return ERR_IO;
            }
        }

        if (row > rows || col > cols || row == 0 || col == 0)
        {
            matrix_free((*mtr));
            return ERR_IO;
        }
        if (!(row > prev_row || col > prev_col))
        {
            matrix_free((*mtr));
            return ERR_IO;
        }
        prev_row = row--;
        prev_col = col--;

        (*mtr)->A[i] = value;
        (*mtr)->JA[i] = col;

        while (current_row < row)
        {
            // Заполняем IA для строк, в которых пока нет ненулевых элементов
            current_row++;
            (*mtr)->IA[current_row] = i; // Начало следующей строки
        }
    }
    if (f != stdin && !feof(f))
    {
        matrix_free((*mtr));
        return ERR_IO;
    }

    // Заполняем IA для оставшихся строк (если они пусты)
    for (size_t i = current_row + 1; i <= rows; i++)
    {
        (*mtr)->IA[i] = nz;
    }
    return OK;
}

void matrix_print(FILE *f, mtr_t *mtr)
{
    size_t curr;
    fprintf(f, "%lu %lu %lu\n", mtr->rows, mtr->cols, mtr->nz);
    for (size_t i = 0; i < mtr->rows; ++i)
    {
        curr = mtr->IA[i];
        while(curr < mtr->IA[i + 1])
        {
            fprintf(f, "%lu %lu %lf\n", i + 1, mtr->JA[curr] + 1, mtr->A[curr]);
            curr++;
        }
    }
}

int vector_read(FILE *f, vector_t **v)
{
    size_t rows, nz;
    if (f == stdin)
    {
        printf("Введите количество строк в векторе-столбце: ");
        if (fscanf(f, "%lu", &rows) != 1)
            return ERR_IO;
        printf("Введите количество ненулевых элементов: ");
        if (fscanf(f, "%lu", &nz) != 1)
            return ERR_IO;
    }
    else
    {
        if (fscanf(f, "%lu %lu\n", &rows, &nz) != 2)
            return ERR_IO;
    }

    (*v) = vector_allocate(rows, nz);

    if ((*v) == NULL)
        return ERR_MEM;

    size_t row, prev_row = 0;
    double value;
    for (size_t i = 0; i < nz; ++i)
    {
        if (f == stdin)
        {
            printf("Элемент №%lu\n", i + 1);
            printf("Введите строку: ");
            if (fscanf(f, "%lu", &row) != 1)
            {
                vector_free((*v));
                return ERR_IO;
            }
            printf("Введите элемент: ");
            if (fscanf(f, "%lf", &value) != 1)
            {
                vector_free((*v));
                return ERR_IO;
            }
        }
        else
        {
            if (fscanf(f, "%lu %lf\n", &row, &value) != 2)
            {
                vector_free((*v));
                return ERR_IO;
            }
        }

        if (row > rows || row == 0)
        {
            vector_free((*v));
            return ERR_IO;
        }
        if (!(row > prev_row))
        {
            vector_free((*v));
            return ERR_IO;
        }
        prev_row = row--;

        (*v)->A[i] = value;
        (*v)->IA[i] = row;
    }
    if (f != stdin && !feof(f))
        return ERR_IO;

    return OK;
}

void vector_print(FILE *f, vector_t *v)
{
    fprintf(f, "%lu %lu\n", v->rows, v->nz);
    for (size_t i = 0; i < v->nz; ++i)
    {
        fprintf(f, "%lu %lf\n", v->IA[i] + 1, v->A[i]);
    }
}
