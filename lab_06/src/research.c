#include "research.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"

#define MAX_NUM_TESTS 1000
#define MAX_STR_LEN 1000

void rnd_st
(char *str, int n)
{
    srand(CLOCK_MONOTONIC_RAW);

    for (int i = 0; i < n - 1; ++i)
    {
        char c = rand() % (256);
        str[i] = c;
    }

    str[n - 1] = '\0';
}

void rem_dup(char *str)
{
    int len = strlen(str);

    if (len <= 1)
    {
        return;
    }

    int tail = 1;

    for (int i = 1; i < len; ++i) {
        int j;
        for (j = 0; j < tail; ++j) {
            if (str[i] == str[j]) {
                break;
            }
        }
        
        if (j == tail) {
            str[tail++] = str[i];
        }
    }

    str[tail] = '\0';
}

void calc_size_tree(struct Node* root, size_t *size)
{
    if (root != NULL)
    {
        calc_size_tree(root->left, size);
        *size += sizeof(struct Node);
        calc_size_tree(root->right, size);
    }
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

double run_tests_str(char *str)
{
    char tmp[MAX_STR_LEN];
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        strcpy(tmp, str);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        rem_dup(tmp);
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
    printf("Реализация с помощью строки:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

double run_tests_tree(char *str)
{
    struct Node *root = NULL;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        root = del_rep_nodes(root);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        free_tree(root);
        root = NULL;
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
    printf("Реализация с помощью дерева:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

double run_tests_tree_find(char *str)
{
    struct Node *root = NULL;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    char s = 'a';
    struct Node *tmp;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        tmp = search(root, s);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        (void)tmp;
        free_tree(root);
        root = NULL;
        test_arr[i] = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

        if (i % 100 == 99)
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
    printf("Реализация с помощью дерева:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

void cmp_del_rep(void)
{
    for (size_t i = 0; i < 99; ++i)
        printf("-");
    for (size_t l_str = 10; l_str < MAX_STR_LEN; l_str += 100)
    {
        printf("\n\033[0;36m");
        double avr1, avr2;

        printf("Длина строки - %lu\n\n", l_str);

        char str[MAX_STR_LEN];
        rnd_st(str, l_str);

        avr1 = run_tests_str(str);
        size_t size1 = sizeof(char) * (l_str);
        printf("Занимаемая память - %ld байт\n", size1);
        
        avr2 = run_tests_tree(str);
        struct Node *root = NULL;
        for (int i = 0; str[i] != '\0'; i++)
            root = insert(root, str[i]);
        size_t size2 = 0;
        calc_size_tree(root, &size2);
        printf("Занимаемая память - %ld байт\n", size2);

        free_tree(root);

        printf("\nРазность производительности = %.2lf нс\n", fabs(avr1 - avr2));
        if (avr1 > avr2)
            printf("Реализация с помощью строки дольше на %lf %%\n", fabs(100 - (100 * avr1 / avr2)));
        else if (avr1 < avr2)
            printf("Реализация с помощью дерева дольше на %lf %%\n", fabs(100 - (100 * avr2 / avr1)));
        printf("\n");

        printf("Разность занимаемой памяти = %d байт\n", abs(size1 - size2));
        if (size1 > size2)
            printf("Реализация с помощью строки больше на %d %%\n", abs(100 - (100 * size1 / size2)));
        else if (size1 < size2)
            printf("Реализация с помощью дерева больше на %d %%\n", abs(100 - (100 * size2 / size1)));
        printf("\n");

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n\033[0;37m");
    }
}

void cmp_find(void)
{
    for (size_t i = 0; i < 99; ++i)
        printf("-");
    for (size_t l_str = 10; l_str < MAX_STR_LEN; l_str += 100)
    {
        printf("\n\033[0;36m");
        double avr2;

        printf("Длина строки - %lu\n\n", l_str);

        char str[MAX_STR_LEN];
        rnd_st(str, l_str);
        
        avr2 = run_tests_tree_find(str);
        (void)avr2;
        struct Node *root = NULL;
        for (int i = 0; str[i] != '\0'; i++)
            root = insert(root, str[i]);
        size_t size2 = 0;
        calc_size_tree(root, &size2);
        printf("Занимаемая память - %ld байт\n", size2);

        free_tree(root);

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n\033[0;37m");
    }
}
