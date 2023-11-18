#include "test_stack.h"
#include "stack_op.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

#define MAX_NUM_TESTS 1000
#define SIZE_ARR 10000

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

double run_tests_arr(arr_stack_t a1, arr_stack_t a2)
{
    arr_stack_t sorted_arr = arr_stack_create();
    arr_stack_t arr1 = arr_stack_create(), arr2 = arr_stack_create();
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        arr_stack_cpy(a1, arr1);
        arr_stack_cpy(a2, arr2);
        arr_stack_make_empty(sorted_arr);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        arr_stack_merge_sort(arr1, arr2, sorted_arr);
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
    arr_stack_destroy(arr1);
    arr_stack_destroy(arr2);
    arr_stack_destroy(sorted_arr);

    avr = calc_mean(test_arr, i);
    printf("Реализация с помощью массива:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

double run_tests_list(list_stack_t l1, list_stack_t l2, freed_stack_t freed_stack)
{
    list_stack_t sorted_list = NULL, list1 = NULL, list2 = NULL;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        list_stack_cpy(l1, &list1, freed_stack);
        list_stack_cpy(l2, &list2, freed_stack);
        list_stack_destroy(sorted_list, freed_stack);
        sorted_list = NULL;
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        list_stack_merge_sort(&list1, &list2, &sorted_list, freed_stack);
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
    list_stack_destroy(sorted_list, freed_stack);
    list_stack_destroy(list1, freed_stack);
    list_stack_destroy(list2, freed_stack);

    avr = calc_mean(test_arr, i);
    printf("Реализация с помощью списка:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

void start_test(int cnt)
{
    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;36m");
    double avr1, avr2;

    arr_stack_t arr1 = arr_stack_create(), arr2 = arr_stack_create();
    list_stack_t list1 = NULL, list2 = NULL;
    freed_stack_t freed_stack = init_freed_stack(100);
    
    int x;

    for (size_t i = 0; i < cnt; ++i)
    {
        if ((x = rand()) % 2 == 0)
        {
            arr_stack_push(arr1, x);
            list1 = list_stack_push(list1, x, freed_stack);
        }
        else
        {
            arr_stack_push(arr2, x);
            list2 = list_stack_push(list2, x, freed_stack);
        }
    }

    avr1 = run_tests_arr(arr1, arr2);
    size_t size1 = sizeof(int) * SIZE_ARR + sizeof(size_t);
    printf("Занимаемая память - %ld байт\n", size1);
    
    size_t size2 = (sizeof(int) + sizeof(int*)) * cnt;
    avr2 = run_tests_list(list1, list2, freed_stack);
    printf("Занимаемая память - %ld байт\n", size2);

    arr_stack_destroy(arr1);
    arr_stack_destroy(arr2);
    list_stack_destroy(list1, freed_stack);
    list_stack_destroy(list2, freed_stack);
    destroy_freed_stack(freed_stack);

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

    for (size_t i = 0; i < 102; ++i)
        printf("-");
    printf("\n\033[0;37m");
}
