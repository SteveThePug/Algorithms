#ifndef GRAPH_H
#define GRAPH_H

#include "array.h"
#include <stdbool.h>

typedef struct
{
	int **adj_mat;
	int num_vtx;
} Graph;

Graph *make_graph(int n);
Graph *clone_graph(Graph *g);
void free_graph(Graph *g);

void print_graph(Graph *g);
bool empty_graph(Graph *g);

void add_edge(Graph *g, int u, int v, int c);
Array *vertex_neighbors(Graph *g, int u);

void randomize_graph(Graph *g, int max);

/**
 * @brief Preforms a depth first search on a graph
 * @param g The graph to search
 * @param u The start vertex
 * @param v The end vertex
 * @return Array of vertecies of the array
 */
Array *dfs_find_path(Graph *g, int u, int v);
Array *bfs_find_path(Graph *g, int u, int v);

Graph *bfs_find_flow(Graph *g, int s, int t);
Graph *dfs_find_flow(Graph *g, int s, int t);

Graph *residual_network(Graph *g, Graph *flow);

Graph *bfs_optimal_flow(Graph *g, int s, int t);
Graph *dfs_optimal_flow(Graph *g, int s, int t);

#endif
