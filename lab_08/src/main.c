#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "graph_list.h"
#include "graph_mtr.h"
#include "research.h"

int main(void)
{
    print_info();
    int choice;
    char tmp[7];

    graph_list_t g_l;
    graph_mtr_t g_m;

    graph_list_t *pg_l = NULL;
    graph_mtr_t *pg_m = NULL;

    graph_list_t tmp_l;
    graph_mtr_t tmp_m;

    while (1)
    {
        print_actions();
        printf("Выберите действие: ");
        if (scanf("%d", &choice) != 1)
            choice = 123;
        fgets(tmp, sizeof(tmp), stdin);

        switch (choice)
        {
            case 1:
                if (pg_m)
                    free_mtr(g_m.matrix, g_m.vertices);
                else
                    pg_m = &g_m;
                create_mtr(pg_m);
                break;
            case 2:
                if (pg_m)
                    print_mtr(pg_m);
                else
                    printf("Граф не введен\n");
                break;
            case 3:
                if (pg_m)
                    print_graph_mtr(pg_m);
                else
                    printf("Граф не введен\n");
                break;
            case 4:
                if (pg_m)
                {
                    tmp_m = copy_graph_mtr(pg_m);
                    floyd_warshall_mtr(&tmp_m);
                    print_shortest_paths_mtr(&tmp_m);
                    free_mtr(tmp_m.matrix, tmp_m.vertices);
                }
                else
                    printf("Граф не введен\n");
                break;
            case 5:
                if (pg_l)
                    free_graph_list(pg_l);
                else
                    pg_l = &g_l;
                create_graph_list(pg_l);
                break;
            case 6:
                if (pg_l)
                    print_list(pg_l);
                else
                    printf("Граф не введен\n");
                break;
            case 7:
                if (pg_l)
                    print_graph_list(pg_l);
                else
                    printf("Граф не введен\n");
                break;
            case 8:
                if (pg_l)
                {
                    tmp_l = copy_graph_list(pg_l);
                    floyd_warshall_list(&tmp_l);
                    print_shortest_paths_list(&tmp_l);
                    free_graph_list(&tmp_l);
                }
                else
                    printf("Граф не введен\n");
                break;
            case 9:
                run_tests();
                break;
            case 0:
                if (pg_m)
                    free_mtr(g_m.matrix, g_m.vertices);
                if (pg_l)
                    free_graph_list(pg_l);
                return 0;
            default:
                printf("Неверная команда\n");
                break;
        }
    }

    return 0;
}
