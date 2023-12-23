#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

typedef struct node
{
    int vertex;
    int weight;
    struct node* next;
} node_t;

typedef struct
{
    node_t** adjacency_list;
    int vertices;
} graph_list_t;

node_t* create_node(int vertex, int weight);

void add_edge_list(graph_list_t* graph, int src, int dest, int weight);

void free_graph_list(graph_list_t* graph);

void create_graph_list(graph_list_t* graph);

void print_list(graph_list_t* graph);

void print_graph_list(graph_list_t* graph);

void floyd_warshall_list(graph_list_t* graph);

void print_shortest_paths_list(graph_list_t* graph);

graph_list_t copy_graph_list(const graph_list_t* original);

#endif
