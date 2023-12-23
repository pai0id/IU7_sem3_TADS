#include "research.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "graph_list.h"
#include "graph_mtr.h"

#define MAX_NUM_TESTS 1000
#define MAX_GRAPH_SIZE 520

static void create_mtr_rnd(graph_mtr_t* graph, size_t n)
{
    graph->vertices = n;

    graph->matrix = alloc_mtr(graph->vertices, graph->vertices);

    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i; j < graph->vertices; j++)
        {
            if (i == j)
            {
                graph->matrix[i][j] = 0;
                continue;
            }

            graph->matrix[i][j] = rand();

            graph->matrix[j][i] = graph->matrix[i][j];
        }
    }
}

static void create_graph_list_rnd(graph_list_t* graph, size_t n)
{
    graph->vertices = n;

    graph->adjacency_list = (node_t**)malloc(graph->vertices * sizeof(node_t*));
    for (int i = 0; i < graph->vertices; i++)
        graph->adjacency_list[i] = NULL;

    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i + 1; j < graph->vertices; j++)
        {
            int weight = rand();

            if (weight != 0)
                add_edge_list(graph, i, j, weight);
        }
    }
}

static size_t calc_size_list(graph_list_t *graph)
{
    size_t cnt = 0;
    for (int i = 0; i < graph->vertices; i++)
    {
        node_t* current = graph->adjacency_list[i];
        while (current != NULL)
        {
            cnt++;
            current = current->next;
        }
    }
    return cnt * sizeof(node_t);
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

double run_tests_mtr(graph_mtr_t *graph)
{
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    
    graph_mtr_t tmp_m;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        tmp_m = copy_graph_mtr(graph);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        floyd_warshall_mtr(&tmp_m);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        free_mtr(tmp_m.matrix, tmp_m.vertices);
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
    printf("Реализация с помощью матрицы:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

double run_tests_list(graph_list_t *graph)
{
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    
    graph_list_t tmp_l;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        tmp_l = copy_graph_list(graph);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        floyd_warshall_list(&tmp_l);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        free_graph_list(&tmp_l);
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
    printf("Реализация с помощью списка:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

void run_tests(void)
{
    for (size_t i = 0; i < 99; ++i)
        printf("-");
    for (size_t n = 10; n <= MAX_GRAPH_SIZE; n += 100)
    {
        printf("\n\033[0;36m");
        double avr1, avr2;

        printf("Размер графа: %lu\n\n", n);

        graph_mtr_t g_m;
        graph_list_t g_l;

        long long key = CLOCK_MONOTONIC_RAW;
        
        srand(key);
        create_mtr_rnd(&g_m, n);
        srand(key);
        create_graph_list_rnd(&g_l, n);
        
        avr1 = run_tests_mtr(&g_m);
        size_t size1 = g_m.vertices * g_m.vertices * sizeof(int);
        printf("Занимаемая память - %ld байт\n", size1);

        avr2 = run_tests_list(&g_l);
        size_t size2 = calc_size_list(&g_l);
        printf("Занимаемая память - %ld байт\n", size2);

        for (size_t i = 0; i < 73; ++i)
            printf("_");
        
        printf("\nРазность производительности = %.2lf нс\n", fabs(avr1 - avr2));
        if (avr1 > avr2)
            printf("Реализация с помощью матрицы дольше на %lf %%\n", fabs(100 - (100 * avr1 / avr2)));
        else if (avr1 < avr2)
            printf("Реализация с помощью списка дольше на %lf %%\n", fabs(100 - (100 * avr2 / avr1)));
        printf("\n");
        printf("Разность занимаемой памяти = %d байт\n", abs(size1 - size2));
        if (size1 > size2)
            printf("Реализация с помощью матрицы больше на %lf %%\n", fabs(100 - (100 * (double)size1 / (double)size2)));
        else if (size1 < size2)
            printf("Реализация с помощью списка больше на %lf %%\n", fabs(100 - (100 * (double)size2 / (double)size1)));
        printf("\n");

        free_mtr(g_m.matrix, g_m.vertices);
        free_graph_list(&g_l);

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n\033[0;37m");
    }
}
