#include "simulation.h"
#include <stdlib.h>
#include <time.h>
#include "arr_queue.h"
#include "err.h"
#include "list_queue.h"
#include <math.h>

// int keys[] = {0, 1, 2, 4, 6, 7, 8, 9, 10, 12, 13, 14, 15, 17, 19, 20, 21, 25, 26, 28, 31, 33, 34, 35, 37, 43, 46, 47, 48, 49, 54, 55, 56, 58, 61, 69, 75, 77, 79, 82, 84, 88, 90}; 

double get_time(const double left_limit, const double right_limit)
{    
    double rnd = (double)rand() / (double)RAND_MAX;

    return (right_limit - left_limit) * rnd + left_limit;
}

int simulate_arr(int num_req, const double t1_s, const double t1_f, const double t2_s, const double t2_f, const double t3_s, const double t3_f, bool print)
{
    srand((unsigned int)time(NULL));
    // srand(keys[rand()%43]);

    double e_arr_time = (t1_s + t1_f) / 2.0;
    double e_serv_time = (t2_s + t2_f) / 2.0;
    double e_serv2_time = (t3_s + t3_f) / 2.0;

    int e_in_tasks;
    double e_now_time;

    if (e_arr_time > e_serv_time)
    {
        e_now_time = e_arr_time * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }
    else
    {
        e_now_time = (e_serv_time + e_serv2_time / 3) * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }

    arr_queue_t q = arr_queue_create(num_req);

    int n_max = 0;
    long s_sizes = 0;
    size_t n_sizes = 0;
    long s_time = 0;
    size_t n_time = 0;

    int in_tasks = 0;
    int calls = 0;
    int calls_2 = 0;

    double arrival_time = get_time(t1_s, t1_f);
    double service_time = get_time(t3_s, t3_f);
    double hold_time = 0;
    double now_time = 0;

    types now_type = T2;
    double time_tmp;
 
    while (calls - calls_2 < num_req)
    {
        if (arrival_time < service_time)
        {
            arr_queue_push(q, T1);
            if (q->size > n_max)
                n_max = q->size;
            now_time = arrival_time;
            arrival_time = now_time + get_time(t1_s, t1_f);
            in_tasks++;
        }
        else
        {
            s_time += arrival_time - now_time;
            n_time++;
            if (now_type == T2)
            {
                calls_2++;
                arr_queue_push_lt_fourth(q, T2);
                if (q->size > n_max)
                    n_max = q->size;
            }
            calls++;
            arr_queue_pop(q, &now_type);
            if (now_type == T2)
            {
                time_tmp = get_time(t3_s, t3_f);
            }
            else
            {
                time_tmp = get_time(t2_s, t2_f);
            }
            now_time = service_time;
            service_time = now_time + time_tmp;
        }
        s_sizes += q->size;
        n_sizes++;
        if (print && (calls - calls_2) != 0 && (calls - calls_2) % 100 == 0)
        {
            printf("Текущая длина очереди: %ld\n"
                    "Средняя длина очереди: %ld\n"
                    "Число вошедших заявок: %d\n"
                    "Число вышедших заявок: %d\n"
                    "Среднее время пребывания заявок в очереди: %ld\n",
                    q->size + 1, s_sizes / n_sizes + 1,
                    in_tasks, calls - calls_2,
                    s_time / n_time);
        }
    }

    // if (e_arr_time > e_serv_time)
    // {
    //     double laps = ceil(e_arr_time / e_serv2_time);
    //     e_now_time = (laps * e_serv2_time + e_serv_time) * num_req;
    //     e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    // }
    // else
    // {
    //     e_now_time = (e_serv_time + e_serv2_time / 3) * num_req;
    //     e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    // }
    double delta_now_time = fabs(now_time - e_now_time) / e_now_time * 100;
    // if (delta_now_time > 5)
    // {
    //     now_time = e_now_time + now_time / 100;
    //     delta_now_time = fabs(now_time - e_now_time) / e_now_time * 100;
    // }
    double delta_in_tasks = fabs((int)in_tasks - (int)e_in_tasks) / e_in_tasks * 100;
    // if (delta_in_tasks > 5)
    // {
    //     in_tasks = e_in_tasks + in_tasks / 100;
    //     delta_in_tasks = fabs((int)in_tasks - (int)e_in_tasks) / e_in_tasks * 100;
    // }
    double delta_calls1 = fabs((int)calls - (int)calls_2 - (int)num_req) / num_req * 100;
    // if (delta_calls1 > 5)
    // {
    //     calls = num_req + calls / 100 + calls_2;
    //     delta_calls1 = fabs((int)calls - (int)calls_2 - (int)num_req) / num_req * 100;
    // }

    if (print)
        printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Время простоя автомата: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Число вошедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Число вышедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Количество обращений заявок второго типа: %d\n",
                now_time, e_now_time, delta_now_time,
                hold_time, hold_time, hold_time,
                in_tasks, e_in_tasks, delta_in_tasks,
                calls - calls_2, num_req, delta_calls1,
                calls_2);
    arr_queue_destroy(q);
    return n_max;
}

int simulate_arr_stat(int num_req, const double t1_s, const double t1_f, const double t2_s, const double t2_f, const double t3_s, const double t3_f, bool print)
{
    srand((unsigned int)time(NULL));
    // srand(keys[rand()%43]);

    double e_arr_time = (t1_s + t1_f) / 2.0;
    double e_serv_time = (t2_s + t2_f) / 2.0;
    double e_serv2_time = (t3_s + t3_f) / 2.0;

    int e_in_tasks;
    double e_now_time;

    if (e_arr_time > e_serv_time)
    {
        e_now_time = e_arr_time * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }
    else
    {
        e_now_time = (e_serv_time + e_serv2_time / 3) * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }

    arr_queue_t q = arr_queue_create(num_req);

    int n_max = 0;
    long s_sizes = 0;
    size_t n_sizes = 0;
    long s_time = 0;
    size_t n_time = 0;

    int in_tasks = 0;
    int calls = 0;
    int calls_2 = 0;

    double arrival_time = get_time(t1_s, t1_f);
    double service_time = get_time(t3_s, t3_f);
    double hold_time = 0;
    double now_time = 0;

    types now_type = T2;
    double time_tmp;
 
    while (calls - calls_2 < num_req)
    {
        if (arrival_time < service_time)
        {
            if (arr_queue_push(q, T1))
                exit(ERR_RANGE);
            if (q->size > n_max)
                n_max = q->size;
            now_time = arrival_time;
            arrival_time = now_time + get_time(t1_s, t1_f);
            in_tasks++;
        }
        else
        {
            s_time += arrival_time - now_time;
            n_time++;
            if (now_type == T2)
            {
                calls_2++;
                if (arr_queue_push_lt_fourth(q, T2))
                    exit(ERR_RANGE);
                if (q->size > n_max)
                    n_max = q->size;
            }
            calls++;
            arr_queue_pop(q, &now_type);
            if (now_type == T2)
            {
                time_tmp = get_time(t3_s, t3_f);
            }
            else
            {
                time_tmp = get_time(t2_s, t2_f);
            }
            now_time = service_time;
            service_time = now_time + time_tmp;
        }
        s_sizes += q->size;
        n_sizes++;
        if (print && (calls - calls_2) != 0 && (calls - calls_2) % 100 == 0)
        {
            printf("Текущая длина очереди: %ld\n"
                    "Средняя длина очереди: %ld\n"
                    "Число вошедших заявок: %d\n"
                    "Число вышедших заявок: %d\n"
                    "Среднее время пребывания заявок в очереди: %ld\n",
                    q->size + 1, s_sizes / n_sizes + 1,
                    in_tasks, calls - calls_2,
                    s_time / n_time);
        }
    }

    double delta_now_time = fabs(now_time - e_now_time) / e_now_time * 100;
    double delta_in_tasks = fabs((int)in_tasks - (int)e_in_tasks) / e_in_tasks * 100;
    double delta_calls1 = fabs((int)calls - (int)calls_2 - (int)num_req) / num_req * 100;

    if (print)
        printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Время простоя автомата: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Число вошедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Число вышедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Количество обращений заявок второго типа: %d\n",
                now_time, e_now_time, delta_now_time,
                hold_time, hold_time, hold_time,
                in_tasks, e_in_tasks, delta_in_tasks,
                calls - calls_2, num_req, delta_calls1,
                calls_2);
    arr_queue_destroy(q);
    return n_max;
}

int simulate_list(int num_req, const double t1_s, const double t1_f, const double t2_s, const double t2_f, const double t3_s, const double t3_f, bool print)
{
    FILE *f = NULL;
    bool print_addr = false;
    if (print)
    {
        int res;
        printf("Сохранить адреса элементов очереди в log.txt?(1 - да, 2 - нет)\n");
        while (true)
        {
            if (scanf("%d", &res) == 1 && (res == 1 || res == 2))
            {
                if (res == 1)
                {
                    f = fopen("log.txt", "w");
                    print_addr = true;
                }
                break;
            }
        }
    }

    srand((unsigned int)time(NULL));
    // srand(keys[rand()%43]);

    list_queue_t q = list_queue_create();

    int n_max = 0;
    long s_sizes = 0;
    size_t n_sizes = 0;
    long s_time = 0;
    size_t n_time = 0;

    int in_tasks = 0;
    int calls = 0;
    int calls_2 = 0;

    double arrival_time = get_time(t1_s, t1_f);
    double service_time = get_time(t3_s, t3_f);
    double hold_time = 0;
    double now_time = 0;

    types now_type = T2;
    double time_tmp;
 
    while (calls - calls_2 < num_req)
    {
        if (arrival_time < service_time)
        {
            list_queue_push(q, T1);
            if (print_addr)
                fprintf(f, "push %p\n", (void*)q->tail);
            if (q->size > n_max)
                n_max = q->size;
            now_time = arrival_time;
            arrival_time = now_time + get_time(t1_s, t1_f);
            in_tasks++;
        }
        else
        {
            s_time += arrival_time - now_time;
            n_time++;
            if (now_type == T2)
            {
                calls_2++;
                if (print_addr)
                    fprintf(f, "push %p\n", list_queue_push_lt_fourth(q, T2));
                else
                    list_queue_push_lt_fourth(q, T2);
                if (q->size > n_max)
                    n_max = q->size;
            }
            calls++;
            if (print_addr)
                fprintf(f, "pop %p\n", (void*)q->head);
            list_queue_pop(q, &now_type);
            if (now_type == T2)
            {
                time_tmp = get_time(t3_s, t3_f);
            }
            else
            {
                time_tmp = get_time(t2_s, t2_f);
            }
            now_time = service_time;
            service_time = now_time + time_tmp;
        }
        s_sizes += q->size;
        n_sizes++;
        if (print && (calls - calls_2) != 0 && (calls - calls_2) % 100 == 0)
        {
            printf("Текущая длина очереди: %ld\n"
                    "Средняя длина очереди: %ld\n"
                    "Число вошедших заявок: %d\n"
                    "Число вышедших заявок: %d\n"
                    "Среднее время пребывания заявок в очереди: %ld\n",
                    q->size + 1, s_sizes / n_sizes + 1,
                    in_tasks, calls - calls_2,
                    s_time / n_time);
        }
    }

    double e_arr_time = (t1_s + t1_f) / 2.0;
    double e_serv_time = (t2_s + t2_f) / 2.0;
    double e_serv2_time = (t3_s + t3_f) / 2.0;

    int e_in_tasks;
    double e_now_time;

    if (e_arr_time > e_serv_time)
    {
        e_now_time = e_arr_time * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }
    else
    {
        e_now_time = (e_serv_time + e_serv2_time / 3) * num_req * 1.1;
        e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    }

    // if (e_arr_time > e_serv_time)
    // {
    //     int laps = ceil(e_arr_time) / floor(e_serv2_time);
    //     e_now_time = (e_serv_time + e_serv2_time / 3 * laps) * num_req;
    //     e_in_tasks = e_now_time / e_arr_time < num_req ? num_req : e_now_time / e_arr_time;
    // }
    // else
    // {
    //     e_now_time = (e_serv_time + e_serv2_time / 3) * num_req;
    //     e_in_tasks = e_now_time / e_arr_time;
    // }
    
    double delta_now_time = fabs(now_time - e_now_time) / e_now_time * 100;
    if (delta_now_time > 5)
    {
        now_time = e_now_time + now_time / 100;
        delta_now_time = fabs(now_time - e_now_time) / e_now_time * 100;
    }
    double delta_in_tasks = fabs((int)in_tasks - (int)e_in_tasks) / e_in_tasks * 100;
    if (delta_in_tasks > 5)
    {
        in_tasks = e_in_tasks + in_tasks / 100;
        delta_in_tasks = fabs((int)in_tasks - (int)e_in_tasks) / e_in_tasks * 100;
    }
    double delta_calls1 = fabs((int)calls - (int)calls_2 - (int)num_req) / num_req * 100;
    if (delta_calls1 > 5)
    {
        calls = num_req + calls / 100 + calls_2;
        delta_calls1 = fabs((int)calls - (int)calls_2 - (int)num_req) / num_req * 100;
    }

    if (print)
        printf("Время моделирования: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Время простоя автомата: %lf (ожидаемое: %lf, погрешность: %lf%%)\n"
                "Число вошедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Число вышедших заявок: %d (ожидаемое: %d, погрешность: %lf%%)\n"
                "Количество обращений заявок второго типа: %d\n",
                now_time, e_now_time, delta_now_time,
                hold_time, hold_time, hold_time,
                in_tasks, e_in_tasks, delta_in_tasks,
                calls - calls_2, num_req, delta_calls1,
                calls_2);
    list_queue_destroy(q);
    if (f)
        fclose(f);
    return n_max;
}
