#include "research.h"
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include "hash_table.h"

#define MAX_NUM_TESTS 1000
#define MAX_STR_LEN 510

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
        *size += 1;
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

struct Node* search_w_cmps(struct Node* root, char key, int *cmps) {
    if (root == NULL || root->data == key) {
        cmps += 1;
        return root;
    }
    *cmps += 1;
    if (key < root->data) {
        return search_w_cmps(root->left, key, cmps);
    }

    return search_w_cmps(root->right, key, cmps);
}

int count_tree_cmps(struct Node *root)
{
    int cmps = 0;

    for (size_t i = 0; i < 100; ++i)
    {
        char c = rand() % (256);
        search_w_cmps(root, c, &cmps);
    }
    return cmps / 100;
}

int search_hash_w_cmps(struct HashTable* hashTable, char key)
{
    int cmps = 1;
    int index = hashFunction(key);
    struct HashNode* currentNode = hashTable->table[index];

    while (currentNode != NULL)
    {
        cmps += 1;
        if (currentNode->key == key)
        {
            return cmps + 1;
        }
        currentNode = currentNode->next;
        cmps += 1;
    }

    return cmps;
}

int count_hash_cmps(struct HashTable* hashTable)
{
    int cmps = 0;
    for (size_t i = 0; i < 100; ++i)
    {
        char c = rand() % (256);
        cmps += search_hash_w_cmps(hashTable, c);
    }
    return cmps / 100;
}

double run_tests_tree(char *str)
{
    struct Node *root = NULL;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    struct Node *tmp;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        char s = rand() % (256);
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        tmp = search(root, s);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        (void)tmp;
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

double run_tests_tree_balanced(char *str)
{
    struct Node *root = NULL;
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;
    struct Node *tmp;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        char s = rand() % (256);
        for (int j = 0; str[j] != '\0'; j++)
            root = insert(root, str[j]);
        root = balance_tree(root);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        tmp = search(root, s);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        (void)tmp;
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
    printf("Реализация с помощью сбаллансированного дерева:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

double run_tests_hash_table(char *str)
{
    struct HashTable table;
    initHashTable(&table);
    size_t i;
    double avr;
    long long test_arr[MAX_NUM_TESTS];
    struct timespec start, end;

    for (i = 0; i < MAX_NUM_TESTS; i++)
    {
        char s = rand() % (256);
        for (int j = 0; str[j] != '\0'; j++)
            hash_insert(&table, str[j]);
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);
        hash_search(&table, s);
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);
        freeHashTable(&table);
        initHashTable(&table);
        
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
    printf("Реализация с помощью хэш-таблицы:\n");
    printf("|  Время, нс  | Кол-во итераций | RSE\n");
    printf("|%12.2lf | %15lu | %.2lf\n", avr, i, calc_rse(i, avr, calc_stdev(test_arr, i, avr)));
    return avr;
}

void run_tests(void)
{
    for (size_t i = 0; i < 99; ++i)
        printf("-");
    for (size_t l_str = 10; l_str <= MAX_STR_LEN; l_str += 100)
    {
        printf("\n\033[0;36m");
        double avr1, avr2, avr3;

        printf("Длина строки - %lu\n\n", l_str);

        char str[MAX_STR_LEN];
        rnd_st(str, l_str);

        int cmp1, cmp2, cmp3;

        struct Node *root = NULL;
        for (int i = 0; str[i] != '\0'; i++)
            root = insert(root, str[i]);
        cmp1 = count_tree_cmps(root);
        size_t size1 = 0;
        calc_size_tree(root, &size1);
        root = balance_tree(root);
        cmp2 = count_tree_cmps(root);
        size_t size3 = sizeof(struct HashNode*) * TABLE_SIZE + size1 * sizeof(struct HashNode);
        size1 *= sizeof(struct Node);
        size_t size2 = size1;
        free_tree(root);
        struct HashTable table;
        initHashTable(&table);
        for (int j = 0; str[j] != '\0'; j++)
            hash_insert(&table, str[j]);
        cmp3 = count_hash_cmps(&table);
        freeHashTable(&table);

        
        avr1 = run_tests_tree(str);
        printf("Занимаемая память - %ld байт\n", size1);
        printf("Количество сравнений - %d\n\n", cmp1);

        avr2 = run_tests_tree_balanced(str);
        printf("Занимаемая память - %ld байт\n", size2);
        printf("Количество сравнений - %d\n\n", cmp2);

        avr3 = run_tests_hash_table(str);
        printf("Занимаемая память - %ld байт\n", size3);
        printf("Количество сравнений - %d\n\n", cmp3);

        for (size_t i = 0; i < 73; ++i)
            printf("_");
        
        printf("\nСравнение дерева и сбалансированного дерева:\n\nРазность производительности = %.2lf нс\n", fabs(avr1 - avr2));
        if (avr1 > avr2)
            printf("Реализация с помощью несбалансированного дольше на %lf %%\n", fabs(100 - (100 * avr1 / avr2)));
        else if (avr1 < avr2)
            printf("Реализация с помощью сбалансированного дольше на %lf %%\n", fabs(100 - (100 * avr2 / avr1)));
        printf("\n");
        printf("Разность занимаемой памяти = %d байт\n", abs(size1 - size2));
        printf("Разность количества сравнений = %d\n", abs(cmp1 - cmp2));
        if (cmp1 > cmp2)
            printf("Реализация с помощью несбалансированного требует больше на %d %%\n", abs(100 - (100 * cmp1 / cmp2)));
        else if (cmp1 < cmp2)
            printf("Реализация с помощью сбалансированного требует больше на %d %%\n", abs(100 - (100 * cmp2 / cmp1)));
        printf("\n");

        for (size_t i = 0; i < 73; ++i)
            printf("_");

        printf("\nСравнение несб. дерева и хэш-таблицы:\n\nРазность производительности = %.2lf нс\n", fabs(avr1 - avr3));
        if (avr1 > avr3)
            printf("Реализация с помощью дерева дольше на %lf %%\n", fabs(100 - (100 * avr1 / avr3)));
        else if (avr1 < avr3)
            printf("Реализация с помощью хэш-таблицы дольше на %lf %%\n", fabs(100 - (100 * avr3 / avr1)));
        printf("\n");
        printf("Разность занимаемой памяти = %d байт\n", abs(size1 - size3));
        if (size1 > size3)
            printf("Реализация с помощью дерева больше на %d %%\n", abs(100 - (100 * size1 / size3)));
        else if (size1 < size3)
            printf("Реализация с помощью хэш-таблицы больше на %d %%\n", abs(100 - (100 * size3 / size1)));
        printf("\n");
        printf("Разность количества сравнений = %d\n", abs(cmp1 - cmp3));
        if (cmp1 > cmp3)
            printf("Реализация с помощью несбалансированного требует больше на %d %%\n", abs(100 - (100 * cmp1 / cmp3)));
        else if (cmp1 < cmp3)
            printf("Реализация с помощью хэш-таблицы требует больше на %d %%\n", abs(100 - (100 * cmp3 / cmp1)));
        printf("\n");

        for (size_t i = 0; i < 73; ++i)
            printf("_");

        printf("\nСравнение сб. дерева и хэш-таблицы:\n\nРазность производительности = %.2lf нс\n", fabs(avr2 - avr3));
        if (avr2 > avr3)
            printf("Реализация с помощью дерева дольше на %lf %%\n", fabs(100 - (100 * avr2 / avr3)));
        else if (avr2 < avr3)
            printf("Реализация с помощью хэш-таблицы дольше на %lf %%\n", fabs(100 - (100 * avr3 / avr2)));
        printf("\n");
        printf("Разность занимаемой памяти = %d байт\n", abs(size2 - size3));
        if (size2 > size3)
            printf("Реализация с помощью дерева больше на %d %%\n", abs(100 - (100 * size2 / size3)));
        else if (size2 < size3)
            printf("Реализация с помощью хэш-таблицы больше на %d %%\n", abs(100 - (100 * size3 / size2)));
        printf("\n");
        printf("Разность количества сравнений = %d\n", abs(cmp2 - cmp3));
        if (cmp2 > cmp3)
            printf("Реализация с помощью сбалансированного требует больше на %d %%\n", abs(100 - (100 * cmp2 / cmp3)));
        else if (cmp2 < cmp3)
            printf("Реализация с помощью хэш-таблицы требует больше на %d %%\n", abs(100 - (100 * cmp3 / cmp2)));
        printf("\n");

        for (size_t i = 0; i < 99; ++i)
            printf("-");
        printf("\n\033[0;37m");
    }
}
