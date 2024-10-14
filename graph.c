#include "graph.h"
#include "list.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

// Allocate the graph
Graph make_graph(int n) {
	Graph g;
	g.num_vtx = n;

	g.adj_mat = (int**)malloc(n * sizeof(int*));
	for (int i=0;i<n;i++) {
		g.adj_mat[i] = (int*)calloc(n, sizeof(int));
	}

	return g;
}

// Free the dynamically allocated graph
void free_graph(Graph* g) {
	int n = g->num_vtx;
	for (int i=0; i<n; i++) {
		free(g->adj_mat[i]);
	}
	free(g->adj_mat);
	g->adj_mat = NULL;
	g->num_vtx = 0;
}

// Print the graph
void print_graph(Graph* g) {
	int n = g->num_vtx;
	for (int i=0; i<n; i++) {
		print_array(g->adj_mat[i], n);
	}
}

// Adds an edge connecting i->j with capacity c
void add_edge(Graph *g, int u, int v, int c) {
	g->adj_mat[u][v] = c;
}

// Get the neighbors of a vertex
int* vertex_neighbors(Graph* g, int u, int* len) {
	int n = g->num_vtx;

	int* nbrs = calloc(n, sizeof(int));
	int nbr_count = 0;

	for (int i=0; i<n; i++) {
		if (g->adj_mat[u][i] > 0) {
			nbrs[nbr_count++] = i;
		}
	}

	int* realloc_nbrs = realloc(nbrs, sizeof(int)*n);
	nbrs = realloc_nbrs;
	*len = nbr_count;
	return nbrs;
}

//Randomize the capacities of a graph
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


//Find a path from vertex u to vertex v
int* dfs_find_path(Graph* g, int u, int v, int* len) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	bool* chk_vtx = calloc(n, sizeof(bool)); 
	chk_vtx[u] = true;
	// Make a stack for what vertices we should explore first and add the start vertex
	List* stack = make_list();
	push(stack, u);
	// Allocate a path with at most n vertices
	int* path = malloc(n*sizeof(int));
	int path_len = 0;

	//Begin exploring
	while (!is_empty(stack)) {
		int current = pop(stack);
		path[path_len++] = current;

		if (current == v) {
			free_list(stack);
			free(chk_vtx);
			*len = path_len;
			return realloc(path, path_len * sizeof(int));
		}

		int nbr_len;
		int* nbrs = vertex_neighbors(g, current, &nbr_len);

		for (int i=0;i<nbr_len;i++) {
			int nbr = nbrs[i];
			if (!chk_vtx[nbr]) {
				push(stack, nbr);
				chk_vtx[nbr] = true;
			}
		}

		free(nbrs);
	}

	free(stack);
	free(chk_vtx);
	*len = 0;
	return realloc(path, 0);
}

int* bfs_find_path(Graph* g, int u, int v, int* len) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	bool* chk_vtx = calloc(n, sizeof(bool)); 
	chk_vtx[u] = true;
	// Make a queue for what vertexes we should explore first and add the start vertex
	List* queue = make_list();
	enqueue(queue, u);
	// Allocate a path with at most n vertexes
	int* path = malloc(n*sizeof(int));
	int path_len = 0;

	//Begin exploring
	while (!is_empty(queue)) {
		int current = dequeue(queue);
		path[path_len++] = current;

		if (current == v) {
			free_list(queue);
			free(chk_vtx);
			*len = path_len;
			return realloc(path, path_len * sizeof(int));
		}

		int nbr_len;
		int* nbrs = vertex_neighbors(g, current, &nbr_len);

		for (int i=0;i<nbr_len;i++) {
			int nbr = nbrs[i];
			if (!chk_vtx[nbr]) {
				enqueue(queue, nbr);
				chk_vtx[nbr] = true;
			}
		}

		free(nbrs);
	}

	free(queue);
	free(chk_vtx);
	*len = 0;
	return realloc(path, 0);
}

// Helper function for printing an array
void print_array(int* arr, int n) {
	for (int i=0; i<n; i++) {
		printf("%2d ", arr[i]);
	}
	printf("\n");
}

// Helper function for initializing an array
void fill_array(int* arr, int n, int v) {
	for (int i=0; i<n; i++) {
		arr[i] = v;
	}
}
