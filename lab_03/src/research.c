#include "research.h"
#include "mtr_alloc.h"
#include "mtr_io.h"
#include "mtr_op.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 1000

void old_matrix_free(double **data, size_t n)
{
    double *min = data[0];
    for (size_t i = 1; i < n; ++i)
        if (data[i] < min)
            min = data[i];
    free(min);
    free(data);
}

double **mtr;
size_t n, m;

double **old_matrix_allocate(size_t n, size_t m)
{
    double **ptrs, *data;
    ptrs = malloc(n * sizeof(double*));
    if (!ptrs)
        return NULL;
    data = malloc(n * m * sizeof(double));
    if (!data)
    {
        free(ptrs);
        return NULL;
    }
    for (size_t i = 0; i < n; i++)
        ptrs[i] = data + i * m;
    return ptrs;
}

void old_matrix_fill_null(double **data, size_t n, size_t m)
{
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            data[i][j] = 0;
}

int old_matrix_mult(double **a, size_t a_n, size_t a_m, double **b, size_t b_n, size_t b_m, double ***c, size_t *c_n, size_t *c_m)
{
    if (a_m != b_n)
        return ERR_RANGE;

    *c_n = a_n;
    *c_m = b_m;
    *c = old_matrix_allocate(*c_n, *c_m);
    if (*c == NULL)
        return ERR_MEM;

    old_matrix_fill_null(*c, *c_n, *c_m);

    for (size_t i = 0; i < a_n; ++i)
        for (size_t j = 0; j < b_m; ++j)
            for (size_t k = 0; k < a_m; ++k)
                (*c)[i][j] += a[i][k] * b[k][j];
    return OK;
}

double **transform_mtr(mtr_t *mtr)
{
    double **data = old_matrix_allocate(mtr->rows, mtr->cols);
    if (data == NULL)
        return NULL;
    old_matrix_fill_null(data, mtr->rows, mtr->cols);
    size_t curr;
    for (size_t i = 0; i < mtr->rows; ++i)
    {
        curr = mtr->IA[i];
        while(curr < mtr->IA[i + 1])
        {
            data[i][mtr->JA[curr]] = mtr->A[curr];
            curr++;
        }
    }
    return data;
}

double **transform_vector(vector_t *v)
{
    double **data = old_matrix_allocate(v->rows, 1);
    if (data == NULL)
        return NULL;
    old_matrix_fill_null(data, v->rows, 1);
    for (size_t i = 0; i < v->nz; ++i)
    {
        data[v->IA[i]][0] = v->A[i];
    }
    return data;
}

void old_matrix_print_coord(FILE *f, double **data, size_t n, size_t m, size_t n_el)
{
    fprintf(f, "%lu %lu %lu\n", n, m, n_el);
    for (size_t i = 0; i < n; ++i)
        for (size_t j = 0; j < m; ++j)
            if (fabs(data[i][j]) >= EPS)
                fprintf(f, "%lu %lu %lf\n", i + 1, j + 1, data[i][j]);
}

//___________________________________________________________________________________

// Функция для вычисления среднего значения
double calc_mean(const long long data[], size_t length)
{
    long long sum = 0;
    for (size_t i = 0; i < length; i++)
        sum += data[i];
    return (double)sum / (double)length;
}

// Функция для вычисления стандартного отклонения
double calc_stdev(const long long data[], size_t length, double avr)
{
    double sum = 0;
    for (size_t i = 0; i < length; i++)
    {
        double diff = data[i] - avr;
        sum += diff * diff;
    }
    return sqrt((double)sum / ((double)length - 1));
}

// Функция для вычисления относительной стандартной ошибки (RSE)
double calc_rse(size_t length, double avr, double stdev)
{
    return stdev / sqrt((double)length) / avr * 100;
}

double run_tests_sparse(mtr_t *mtr, vector_t *v)
{
    vector_t *res;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        matrix_mult(mtr, v, &res);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        vector_free(res);

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 5)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    printf("Умножение матрицы на вектор-столбец, применяя алгоритм работы с разреженными матрицами:\n");
    printf("Кол-во элементов | Время, нс | Кол-во итераций | RSE\n");
    printf("%16lu | %9.2lf | %15lu | %.2lf\n", mtr->cols * mtr->rows, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", sizeof(mtr_t*) + sizeof(mtr_t) + sizeof(double) * mtr->nz + sizeof(size_t) * mtr->nz + sizeof(size_t) * mtr->rows);
    return avr;
}

double run_tests_old(double **mtr, size_t n_mtr, size_t m_mtr, double **v, size_t n_v, size_t m_v)
{
    double **res;
    size_t nres, mres;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        old_matrix_mult(mtr, n_mtr, m_mtr, v, n_v, m_v, &res, &nres, &mres);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        old_matrix_free(res, nres);

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 5)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    printf("Умножение матрицы на вектор-столбец, применяя стандартный алгоритм:\n");
    printf("Кол-во элементов | Время, нс | Кол-во итераций | RSE\n");
    printf("%16lu | %9.2lf | %15lu | %.2lf\n", n_mtr * m_mtr, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", n_mtr * sizeof(double*) + n_mtr * m_mtr * sizeof(double));
    return avr;
}

int cmp_methods(mtr_t *mtr, vector_t *v)
{
    if (mtr == NULL)
        return ERR_NO_MTR;
    else if (v == NULL)
        return ERR_NO_V;

    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;36m");
    double avr1, avr2;

    double part = (double)mtr->nz * 100 / (mtr->cols * mtr->rows);
    printf("Размер матрицы: %luх%lu = %lu элементов\n%lf%% матрицы - ненулевые элементы\n\n",
    mtr->rows, mtr->cols, mtr->cols * mtr->rows, part);

    avr1 = run_tests_sparse(mtr, v);
    double **old_mtr = transform_mtr(mtr);
    if (old_mtr == NULL)
        return ERR_MEM;
    double **old_v = transform_vector(v);
    if (old_v == NULL)
    {
        old_matrix_free(old_mtr, mtr->rows);
        return ERR_MEM;
    }
    avr2 = run_tests_old(old_mtr, mtr->rows, mtr->cols, old_v, v->rows, 1);
    old_matrix_free(old_mtr, mtr->rows);
    old_matrix_free(old_v, v->rows);

    printf("Разность = %.2lf нс\n\n", fabs(avr1 - avr2));
    if (avr1 > avr2)
        printf("Обработка обычной матрицы быстрее на %lf %%\n", 100 - (100 * avr2 / avr1));
    else if (avr1 < avr2)
        printf("Обработка разреженной матрицы быстрее на %lf %%\n", 100 - (100 * avr1 / avr2));
    printf("\n");

    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;37m");
    return OK;
}