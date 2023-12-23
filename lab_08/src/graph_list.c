#include "graph_list.h"

node_t* create_node(int vertex, int weight)
{
    node_t* new_node = (node_t*)malloc(sizeof(node_t));
    new_node->vertex = vertex;
    new_node->weight = weight;
    new_node->next = NULL;
    return new_node;
}

void add_edge_list(graph_list_t* graph, int src, int dest, int weight)
{
    node_t* new_node = create_node(dest, weight);
    new_node->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = new_node;

    new_node = create_node(src, weight);
    new_node->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = new_node;
}

void free_graph_list(graph_list_t* graph)
{
    for (int i = 0; i < graph->vertices; i++)
    {
        node_t* current = graph->adjacency_list[i];
        while (current != NULL)
        {
            node_t* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(graph->adjacency_list);
}

void create_graph_list(graph_list_t* graph)
{
    printf("Введите количество вершин графа: ");
    char tmp[7];
    while (scanf("%d", &graph->vertices) != 1 || graph->vertices <= 0)
    {
        printf("Некорректный ввод\n");
        fgets(tmp, sizeof(tmp), stdin);
    }

    graph->adjacency_list = (node_t**)malloc(graph->vertices * sizeof(node_t*));
    for (int i = 0; i < graph->vertices; i++)
        graph->adjacency_list[i] = NULL;

    printf("Введите веса ребер:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i + 1; j < graph->vertices; j++)
        {
            int weight;
            printf("Введите вес ребра между вершинами %d и %d: ", i + 1, j + 1);
            while (scanf("%d", &weight) != 1 || weight < 0)
            {
                printf("Некорректный ввод\n");
                fgets(tmp, sizeof(tmp), stdin);
            }

            if (weight != 0)
                add_edge_list(graph, i, j, weight);
        }
    }
}

void print_list(graph_list_t* graph)
{
    printf("Список смежности:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        printf("Вершина %d:\n", i + 1);
        node_t* current = graph->adjacency_list[i];
        while (current != NULL)
        {
            printf(" -> %d(вес %d)", current->vertex + 1, current->weight);
            current = current->next;
        }
        printf(" -> NULL\n");
    }
}

void print_graph_list(graph_list_t* graph)
{
   FILE *f = fopen("graph.gv", "w");

    fprintf(f, "graph graph_pic {\n");

    for (size_t i = 0; i < graph->vertices; i++)
    {
        node_t* current = graph->adjacency_list[i];
        while (current != NULL && i <= current->vertex)
        {
            fprintf(f, "%zu -- %d [label=\"%.1d\"];\n", i + 1, current->vertex + 1, current->weight);
            current = current->next;
        }
    }
    for (size_t i = 0; i < graph->vertices; i++)
    {
        int is_sep = 1;
        node_t* current = graph->adjacency_list[i];
        while (current != NULL && i <= current->vertex)
        {
            if (current->weight)
                is_sep = 0;
            current = current->next;
        }
        if (is_sep)
            fprintf(f, "%zu -- %zu [color=white];\n", i + 1, i + 1);
    }
    fprintf(f, "}\n");

    fclose(f);

    system("dot -Tpng graph.gv > graph.png");
    system("open graph.png");
}

void floyd_warshall_list(graph_list_t* graph)
{
    int vertices = graph->vertices;
    int** distance = (int**)malloc(vertices * sizeof(int*));

    for (int i = 0; i < vertices; i++)
    {
        distance[i] = (int*)malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++)
        {
            if (i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = INF;
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        node_t* current = graph->adjacency_list[i];
        while (current != NULL)
        {
            distance[i][current->vertex] = current->weight;
            distance[current->vertex][i] = current->weight;
            current = current->next;
        }
    }

    for (int k = 0; k < vertices; k++)
    {
        for (int i = 0; i < vertices; i++)
        {
            for (int j = 0; j < vertices; j++)
            {
                if (distance[i][k] != INF && distance[k][j] != INF &&
                    distance[i][k] + distance[k][j] < distance[i][j])
                {
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            if (distance[i][j] != INF && i != j)
            {
                add_edge_list(graph, i, j, distance[i][j]);
            }
        }
    }
    for (int i = 0; i < vertices; i++)
    {
        free(distance[i]);
    }
    free(distance);
}

void print_shortest_paths_list(graph_list_t* graph)
{
    printf("Кратчайшие пути:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i + 1; j < graph->vertices; j++)
        {
            int path_weight = INF;
            node_t* current = graph->adjacency_list[i];
            while (current != NULL)
            {
                if (current->vertex == j && current->weight < path_weight)
                {
                    path_weight = current->weight;
                    break;
                }
                current = current->next;
            }

            if (path_weight != INF && path_weight != 0)
            {
                printf("Путь между вершинами %d и %d: Вес - %d\n", i + 1, j + 1, path_weight);
            }
            else
            {
                printf("Путь между вершинами %d и %d не существует\n", i + 1, j + 1);
            }
        }
    }
}

static node_t *list_add_tail(node_t *head, node_t *new)
{
    if (!head)
        return new;
    node_t *curr = head;
    while (curr->next)
        curr = curr->next;
    curr->next = new;
    return head;
}

graph_list_t copy_graph_list(const graph_list_t* original)
{
    graph_list_t graph;
    graph.vertices = original->vertices;

    graph.adjacency_list = (node_t**)malloc(graph.vertices * sizeof(node_t*));
    for (int i = 0; i < graph.vertices; i++)
        graph.adjacency_list[i] = NULL;

    for (int i = 0; i < graph.vertices; i++)
    {
        node_t* current = original->adjacency_list[i];
        while (current != NULL)
        {
            node_t *new_node = create_node(current->vertex, current->weight);
            graph.adjacency_list[i] = list_add_tail(graph.adjacency_list[i], new_node);
            current = current->next;
        }
    }

    return graph;
}

