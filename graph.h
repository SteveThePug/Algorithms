#ifndef GRAPH_H
#define GRAPH_H

#include "array.h"

typedef struct {
	int** adj_mat;
	int num_vtx;
} Graph;

Graph* make_graph(int n);
void free_graph(Graph* g);

void print_graph(Graph* g);

void add_edge(Graph* g, int u, int v, int c);
Array* vertex_neighbors(Graph* g, int u);

void randomize_graph(Graph* g, int max);

/**
 * @brief Preforms a depth first search on a graph
 * @param g The graph to search
 * @param u The start vertex
 * @param v The end vertex
 * @return Array of vertecies of the array
 */
Array* dfs_find_path(Graph* g, int u, int v);
Array* bfs_find_path(Graph* g, int u, int v);

Graph* residual_network(Graph* g, Array* path);

#endif