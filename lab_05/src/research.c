#include "research.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "simulation.h"
#include "arr_queue.h"
#include "list_queue.h"

#define MAX_NUM_TESTS 10000

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

double run_tests_arr(size_t num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out, size_t *size)
{
    size_t i;
    int n_max = 0, n_curr;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        n_curr = simulate_arr(num_req, t1_in, t1_out, t2_in, t2_out, t3_in, t3_out, false);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        n_max = n_max < n_curr ? n_curr : n_max;

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 2)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    printf("Реализация с помощью динамического массива:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    size_t size1 = sizeof(arr_queue_type) + sizeof(types) * n_max;
    *size = size1;
    printf("Занимаемая память - %ld байт\n", size1);
    return avr;
}

double run_tests_arr_stat(size_t num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out, size_t *size)
{
    size_t i;
    int n_max = 0, n_curr;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        n_curr = simulate_arr_stat(num_req, t1_in, t1_out, t2_in, t2_out, t3_in, t3_out, false);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        n_max = n_max < n_curr ? n_curr : n_max;

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 2)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    printf("Реализация с помощью статического массива:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    size_t size1 = sizeof(arr_queue_type) + sizeof(types) * n_max;
    *size = size1;
    printf("Занимаемая память - %ld байт\n", size1);
    return avr;
}

double run_tests_list(size_t num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out, size_t *size)
{
    size_t i;
    int n_max = 0, n_curr;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        n_curr = simulate_list(num_req, t1_in, t1_out, t2_in, t2_out, t3_in, t3_out, false);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        n_max = n_max < n_curr ? n_curr : n_max;

        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 10 == 9)
        {
            avr = calc_mean(test_arr, i + 1);
            if (calc_rse(i + 1, avr, calc_stdev(test_arr, i + 1, avr)) <= 2)
            {
                i++;
                break;
            }
        }
    }

    avr = calc_mean(test_arr, i);
    printf("Реализация с помощью списка:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    size_t size2 = sizeof(struct list_queue_type) + sizeof(struct node_t) * n_max;
    *size = size2;
    printf("Занимаемая память - %ld байт\n", size2);
    return avr;
}

void test_sim(size_t num_req, const double t1_in, const double t1_out, const double t2_in, const double t2_out, const double t3_in, const double t3_out)
{
    for (size_t i = 0; i < 99; ++i)
        printf("-");
    
    printf("\n\033[0;36m");
    double avr1, avr2;
    size_t size1, size2;

    avr1 = run_tests_arr_stat(num_req, t1_in, t1_out, t2_in, t2_out, t3_in, t3_out, &size1);
    
    avr2 = run_tests_list(num_req, t1_in, t1_out, t2_in, t2_out, t3_in, t3_out, &size2);

    printf("\nРазность производительности = %.2lf нс\n", fabs(avr1 - avr2));
    if (avr1 > avr2)
        printf("Реализация с помощью массива дольше на %lf %%\n", fabs(100 - (100 * avr1 / avr2)));
    else if (avr1 < avr2)
        printf("Реализация с помощью списка дольше на %lf %%\n", fabs(100 - (100 * avr2 / avr1)));
    printf("\n");

    printf("Разность занимаемой памяти = %d байт\n", abs(size1 - size2));
    if (size1 > size2)
        printf("Реализация с помощью массива больше на %d %%\n", abs(100 - (100 * size1 / size2)));
    else if (size1 < size2)
        printf("Реализация с помощью списка больше на %d %%\n", abs(100 - (100 * size2 / size1)));
    printf("\n");

    for (size_t i = 0; i < 99; ++i)
        printf("-");
    printf("\n\033[0;37m");
}
