#include <stdio.h>
#include <stdlib.h>
#include "graph_mtr.h"

int** alloc_mtr(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int*)malloc(cols * sizeof(int));
    return matrix;
}

void free_mtr(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

void create_mtr(graph_mtr_t* graph)
{
    printf("Введите количество вершин графа: ");
    char tmp[7];
    while (scanf("%d", &graph->vertices) != 1 || graph->vertices <= 0)
    {
        printf("Некорректный ввод\n");
        fgets(tmp, sizeof(tmp), stdin);
    }

    graph->matrix = alloc_mtr(graph->vertices, graph->vertices);

    printf("Введите веса ребер:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i; j < graph->vertices; j++)
        {
            if (i == j)
            {
                graph->matrix[i][j] = 0;
                continue;
            }

            printf("Введите вес ребра между вершинами %d и %d: ", i + 1, j + 1);
            while (scanf("%d", &graph->matrix[i][j]) != 1 || graph->matrix[i][j] < 0)
            {
                printf("Некорректный ввод\n");
                fgets(tmp, sizeof(tmp), stdin);
            }

            graph->matrix[j][i] = graph->matrix[i][j];
        }
    }
}

void print_mtr(graph_mtr_t* graph)
{
    printf("Матрица связности (%d x %d):\n", graph->vertices, graph->vertices);
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
            printf("%d\t", graph->matrix[i][j]);
        printf("\n");
    }
}

void print_graph_mtr(graph_mtr_t *graph_mtr)
{
    FILE *f = fopen("graph.gv", "w");

    fprintf(f, "graph graph_pic {\n");

    for (size_t i = 0; i < (size_t)graph_mtr->vertices; ++i)
    {
        for (size_t j = i; j < (size_t)graph_mtr->vertices; ++j)
        {
            if (graph_mtr->matrix[i][j])
                fprintf(f, "%zu -- %zu [label=\"%.1d\"];\n", i + 1, j + 1, graph_mtr->matrix[i][j]);
        }
    }
    for (size_t i = 0; i < (size_t)graph_mtr->vertices; ++i)
    {
        int is_sep = 1;
        for (size_t j = i; j < (size_t)graph_mtr->vertices; ++j)
        {
            if (graph_mtr->matrix[i][j])
                is_sep = 0;
        }
        if (is_sep)
            fprintf(f, "%zu -- %zu [color=white];\n", i + 1, i + 1);
    }
    fprintf(f, "}\n");

    fclose(f);

    system("dot -Tpng graph.gv > graph.png");
    system("open graph.png");
}

void floyd_warshall_mtr(graph_mtr_t* graph)
{
    int i, j, k;

    for (k = 0; k < graph->vertices; k++)
    {
        for (i = 0; i < graph->vertices; i++)
        {
            for (j = i + 1; j < graph->vertices; j++)
            {
                if (graph->matrix[i][k] != 0 && graph->matrix[k][j] != 0)
                {
                    int through_k = graph->matrix[i][k] + graph->matrix[k][j];
                    if (graph->matrix[i][j] == 0 || through_k < graph->matrix[i][j])
                    {
                        graph->matrix[i][j] = through_k;
                        graph->matrix[j][i] = through_k;
                    }
                }
            }
        }
    }
}

void print_shortest_paths_mtr(graph_mtr_t* graph)
{
    printf("Кратчайшие пути между всеми парами вершин:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i + 1; j < graph->vertices; j++)
        {
            printf("Кратчайший путь между вершинами %d и %d: ", i + 1, j + 1);
            int distance = graph->matrix[i][j];
            if (distance == INF || distance == 0)
                printf("Нет пути\n");
            else
                printf("%d\n", distance);
        }
    }
}

graph_mtr_t copy_graph_mtr(const graph_mtr_t* original)
{
    graph_mtr_t copy;

    copy.vertices = original->vertices;

    copy.matrix = alloc_mtr(copy.vertices, copy.vertices);

    for (int i = 0; i < copy.vertices; i++)
        for (int j = 0; j < copy.vertices; j++)
            copy.matrix[i][j] = original->matrix[i][j];

    return copy;
}
