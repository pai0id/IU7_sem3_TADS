#ifndef GRAPH_MTR_H
#define GRAPH_MTR_H

#include <limits.h>

#define INF INT_MAX

typedef struct
{
    int** matrix;
    int vertices;
} graph_mtr_t;

int** alloc_mtr(int rows, int cols);

void free_mtr(int** matrix, int rows);

void create_mtr(graph_mtr_t* graph);

void print_mtr(graph_mtr_t* graph);

void print_graph_mtr(graph_mtr_t *graph_mtr);

void floyd_warshall_mtr(graph_mtr_t* graph);

void print_shortest_paths_mtr(graph_mtr_t* graph);

graph_mtr_t copy_graph_mtr(const graph_mtr_t* original);

#endif
