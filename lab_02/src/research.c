#include "research.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

double run_tests_bubble(struct book_t *pbooks, size_t n)
{
    struct book_t books[N];
    memcpy(books, pbooks, n * sizeof(struct book_t));
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        bubble_sort_book_arr(books, n);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
    printf("Сортировка пузырьком массива структур:\n");
    printf("Размер массива | Время, нс | Кол-во итераций | RSE\n");
    printf("%14lu | %9.2lf | %15lu | %.2lf\n", n, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", n * sizeof(struct book_t));
    return avr;
}

double run_tests_bubble_id(struct book_t *books, size_t n, size_t *p_id_arr)
{
    size_t id_arr[N];
    memcpy(id_arr, p_id_arr, n * sizeof(size_t));
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        bubble_sort_book_id_arr(books, n, id_arr);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
    printf("Сортировка пузырьком массива ключей:\n");
    printf("Размер массива | Время, нс | Кол-во итераций | RSE\n");
    printf("%14lu | %9.2lf | %15lu | %.2lf\n", n, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", n * sizeof(struct book_t) + n * sizeof(size_t));
    return avr;
}

double run_tests_qsort(struct book_t *pbooks, size_t n)
{
    struct book_t books[N];
    memcpy(books, pbooks, n * sizeof(struct book_t));
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        qsort_book_arr(books, 0, n - 1);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
    printf("Быстрая сортировка массива структур:\n");
    printf("Размер массива | Время, нс | Кол-во итераций | RSE\n");
    printf("%14lu | %9.2lf | %15lu | %.2lf\n", n, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", n * sizeof(struct book_t));
    return avr;
}

double run_tests_qsort_id(struct book_t *books, size_t n, size_t *p_id_arr)
{
    size_t id_arr[N];
    memcpy(id_arr, p_id_arr, n * sizeof(size_t));
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        qsort_book_id_arr(books, 0, n - 1, id_arr);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
    printf("Быстрая сортировка массива ключей:\n");
    printf("Размер массива | Время, нс | Кол-во итераций | RSE\n");
    printf("%14lu | %9.2lf | %15lu | %.2lf\n", n, avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    printf("Занимаемая паямть - %ld байт\n", n * sizeof(struct book_t) + n * sizeof(size_t));
    return avr;
}

double run_tests_get_num_by_id(struct book_t *books, size_t n, size_t *p_id_arr)
{
    size_t id_arr[N];
    memcpy(id_arr, p_id_arr, n * sizeof(size_t));
    qsort_book_id_arr(books, 0, n - 1, id_arr);
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        for (size_t i = 0; i < n; ++i)
            (void)books[id_arr[i]];
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

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
    printf("Время выборки данных из основной таблицы с использованием таблицы ключей:\n");
    printf("Время, нс | Кол-во итераций | RSE\n");
    printf("%9.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

void run_tests(struct book_t *books, size_t n, size_t *id_arr)
{
    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;36m");
    double avr1, avr2, avr3, avr4;
    avr1 = run_tests_bubble(books, n);
    avr2 = run_tests_bubble_id(books, n, id_arr);
    printf("Разность = %.2lf нс\n\n", fabs(avr1 - avr2));
    if (avr1 > avr2)
        printf("Сортировка с помощью ключей быстрее на %lf %%\n", 100 - (100 * avr2 / avr1));
    else if (avr1 < avr2)
        printf("Сортировка массива структур быстрее на %lf %%\n", 100 - (100 * avr1 / avr2));
    printf("Метод ключей занимает на %ld байт больше памяти\n", sizeof(size_t) * n);
    printf("\n");

    avr3 = run_tests_qsort(books, n);
    avr4 = run_tests_qsort_id(books, n, id_arr);
    printf("Разность = %.2lf нс\n\n", fabs(avr3 - avr4));
    if (avr3 > avr4)
        printf("Сортировка с помощью ключей быстрее на %lf %%\n", 100 - (100 * avr4 / avr3));
    else if (avr3 < avr4)
        printf("Сортировка массива структур быстрее на %lf %%\n", 100 - (100 * avr3 / avr4));
    printf("Метод ключей занимает на %ld байт больше памяти\n", sizeof(size_t) * n);
    printf("\n");

    run_tests_get_num_by_id(books, n, id_arr);
    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;37m");
}

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

/// Ввод упорядоченного массива
void input_sorted(int arr[], size_t a_size)
{
    for (size_t i = 0; i < a_size; ++i)
        arr[i] = i + 1;
}

void input_rand(int arr[], size_t a_size)
{
    for (size_t i = 0; i < a_size; ++i)
        arr[i] = rand();
}
