#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulation.h"
#include "research.h"

int main(void)
{
    int num_req = 1000;
    double t1_s = 0, t1_f = 5;
    double t2_s = 0, t2_f = 4;
    double t3_s = 0, t3_f = 4;

    int choice;
    double tmp;
    int tmp_n;
    char tmp_s[7];

    while (1)
    {
        printf("1. Запустить симуляцию для очереди реализованной динамическим массивом\n");
        printf("2. Запустить симуляцию для очереди реализованной статическим массивом\n");
        printf("3. Запустить симуляцию для очереди реализованной списком\n");
        printf("4. Изменить параметры\n");
        printf("5. Оценка эффективности программы (стат. массив и список)\n");
        printf("0. Выход\n");
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1)
            choice = 123;
        fgets(tmp_s, sizeof(tmp_s), stdin);

        printf("\033[0;36m");
        switch (choice)
        {
            case 1:
                simulate_arr(num_req, t1_s, t1_f, t2_s, t2_f, t3_s, t3_f, true);
                break;
            case 2:
                simulate_arr_stat(num_req, t1_s, t1_f, t2_s, t2_f, t3_s, t3_f, true);
                break;
            case 3:
                simulate_list(num_req, t1_s, t1_f, t2_s, t2_f, t3_s, t3_f, true);
                break;
            case 4:
                printf("T1:\n");
                printf("От: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t1_s = tmp;
                printf("До: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t1_f = tmp;
                printf("T2:\n");
                printf("От: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t2_s = tmp;
                printf("До: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t2_f = tmp;
                printf("T3:\n");
                printf("От: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t3_s = tmp;
                printf("До: ");
                if (scanf("%lf", &tmp) != 1 || tmp < 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                t3_f = tmp;
                printf("Количество заявок: ");
                if (scanf("%d", &tmp_n) != 1 || tmp_n <= 0)
                {
                    printf("Ошибка ввода\n");
                    break;
                }
                fgets(tmp_s, sizeof(tmp_s), stdin);
                num_req = tmp_n;
                break;
            case 5:
                test_sim(num_req, t1_s, t1_f, t2_s, t2_f, t3_s, t3_f);
                break;
            case 0:
                return 0;
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
        printf("\033[0;37m");
    }

    return 0;
}
