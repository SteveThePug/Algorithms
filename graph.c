#include "graph.h"
#include "list.h"
#include "array.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// Allocate a graph
Graph* make_graph(int n) {
	Graph* g = calloc(1, sizeof(Graph));
	g->num_vtx = n;

	g->adj_mat = (int**)malloc(n * sizeof(int*));
	for (int i=0;i<n;i++) {
		g->adj_mat[i] = (int*)calloc(n, sizeof(int));
	}

	return g;
}

// Free a graph
void free_graph(Graph* g) {
	int n = g->num_vtx;
	for (int i=0; i<n; i++) {
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);
	g->adj_mat = NULL;
	g->num_vtx = 0;
	free(g);
}

// Print the graph
void print_graph(Graph* g) {
	int n = g->num_vtx;
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			printf("%d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

// Adds an edge connecting i->j with capacity c
void add_edge(Graph *g, int u, int v, int c) {
	g->adj_mat[u][v] = c;
}

// Get the neighbors of a vertex
Array* vertex_neighbors(Graph* g, int u) {
	int n = g->num_vtx;

	Array* nbrs = make_array(n);
	int nbr_count = 0;

	for (int i=0; i<n; i++) {
		if (g->adj_mat[u][i] > 0) {
			nbrs->arr[nbr_count++] = i;
		}
	}

	resize_array(nbrs, nbr_count);
	return nbrs;
}

//Generate a graph with random edge capacities
void randomize_graph(Graph* g, int max) {
	int n = g->num_vtx;
	srand(time(NULL));

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			g->adj_mat[i][j] = rand() % max;
		}
		// Make sure diagonal is 0
		g->adj_mat[i][i] = 0;
	}
}

//Find a path from vertex u to vertex v using depth first search
Array* dfs_find_path(Graph* g, int u, int v) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	Array* chk_vtx = make_array(n);
	fill_array(chk_vtx, false);
	chk_vtx->arr[u] = true;
	// Make a stack for what vertices we should explore first and add the start vertex
	List* stack = make_list();
	push(stack, u);
	// Allocate arrays for path and parent tracking
	Array* path = make_array(n);
	Array* parent = make_array(n);
	fill_array(parent, -1);

	//Begin exploring
	while (!is_empty(stack)) {
		int current = pop(stack);
		if (current == v) {
			// Reconstruct the path
			int path_len = 0;
			int node = v;
			while (node != -1) {
				path->arr[path_len++] = node;
				node = parent->arr[node];
			}
			free_list(stack);
			free_array(chk_vtx);
			free_array(parent);
			resize_array(path, path_len);
			reverse_array(path);
			return path;
		}

		Array* nbrs = vertex_neighbors(g, current);
		for (int i = 0; i < nbrs->n; i++) {
			int nbr = nbrs->arr[i];
			if (!chk_vtx->arr[nbr]) {
				push(stack, nbr);
				chk_vtx->arr[nbr] = true;
				parent->arr[nbr] = current;
			}
		}

		free_array(nbrs);
	}

	free_list(stack);
	free_array(chk_vtx);
	free_array(parent);
	free_array(path);
	return NULL;
}

//Find a path from vertex u to vertex v using breadth first search
Array* bfs_find_path(Graph* g, int u, int v) {
	int n = g->num_vtx;
	// Make a array for checking if we have looked at the vertex
	Array* chk_vtx = make_array(n);
	fill_array(chk_vtx, false);
	chk_vtx->arr[u] = true;
	// Make a queue for what vertices we should explore first and add the start vertex
	List* queue = make_list();
	enqueue(queue, u);
	// Allocate arrays for path and parent tracking
	Array* path = make_array(n);
	Array* parent = make_array(n);
	fill_array(parent, -1);

	//Begin exploring
	while (!is_empty(queue)) {
		int current = dequeue(queue);

		if (current == v) {
			// Reconstruct the path
			int path_len = 0;
			int node = v;
			while (node != -1) {
				path->arr[path_len++] = node;
				node = parent->arr[node];
			}
			free_list(queue);
			free_array(chk_vtx);
			free_array(parent);
			resize_array(path, path_len);
			reverse_array(path);
			return path;
		}

		Array* nbrs = vertex_neighbors(g, current);
		for (int i = 0; i < nbrs->n; i++) {
			int nbr = nbrs->arr[i];
			if (!chk_vtx->arr[nbr]) {
				enqueue(queue, nbr);
				chk_vtx->arr[nbr] = true;
				parent->arr[nbr] = current;
			}
		}
		free_array(nbrs);
	}

	free_list(queue);
	free_array(chk_vtx);
	free_array(parent);
	free_array(path);
	return NULL;
}

//Compute the residual flow matrix
// Graph* residual_network(Graph* g, int* flow, int len)
