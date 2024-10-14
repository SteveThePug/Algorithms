#include "graph.h"
#include "list.h"

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
int* dfs_find_path(Graph* g, int u, int v, int* len) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	bool* chk_vtx = calloc(n, sizeof(bool)); 
	// Make a stack for what vertices we should explore first and add the start vertex
	List* stack = make_list();
	push(stack, u);
	// Allocate arrays for path and parent tracking
	int* path = malloc(n * sizeof(int));
	int* parent = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}

	//Begin exploring
	while (!is_empty(stack)) {
		int current = pop(stack);

		if (current == v) {
			// Reconstruct the path
			int path_len = 0;
			int node = v;
			while (node != -1) {
				path[path_len++] = node;
				node = parent[node];
			}
			// Reverse the path
			for (int i = 0; i < path_len / 2; i++) {
				int temp = path[i];
				path[i] = path[path_len - 1 - i];
				path[path_len - 1 - i] = temp;
			}
			free_list(stack);
			free(chk_vtx);
			free(parent);
			*len = path_len;
			return realloc(path, path_len * sizeof(int));
		}

		if (!chk_vtx[current]) {
			chk_vtx[current] = true;

			int nbr_len;
			int* nbrs = vertex_neighbors(g, current, &nbr_len);

			for (int i = nbr_len - 1; i >= 0; i--) {
				int nbr = nbrs[i];
				if (!chk_vtx[nbr]) {
					push(stack, nbr);
					parent[nbr] = current;
				}
			}

			free(nbrs);
		}
	}

	free_list(stack);
	free(chk_vtx);
	free(parent);
	free(path);
	*len = 0;
	return NULL;
}

//Find a path from vertex u to vertex v using breadth first search
int* bfs_find_path(Graph* g, int u, int v, int* len) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	bool* chk_vtx = calloc(n, sizeof(bool)); 
	chk_vtx[u] = true;
	// Make a queue for what vertices we should explore first and add the start vertex
	List* queue = make_list();
	enqueue(queue, u);
	// Allocate arrays for path and parent tracking
	int* path = malloc(n * sizeof(int));
	int* parent = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}

	//Begin exploring
	while (!is_empty(queue)) {
		int current = dequeue(queue);

		if (current == v) {
			// Reconstruct the path
			int path_len = 0;
			int node = v;
			while (node != -1) {
				path[path_len++] = node;
				node = parent[node];
			}
			// Reverse the path
			for (int i = 0; i < path_len / 2; i++) {
				int temp = path[i];
				path[i] = path[path_len - 1 - i];
				path[path_len - 1 - i] = temp;
			}
			free_list(queue);
			free(chk_vtx);
			free(parent);
			*len = path_len;
			return realloc(path, path_len * sizeof(int));
		}

		int nbr_len;
		int* nbrs = vertex_neighbors(g, current, &nbr_len);

		for (int i = 0; i < nbr_len; i++) {
			int nbr = nbrs[i];
			if (!chk_vtx[nbr]) {
				enqueue(queue, nbr);
				chk_vtx[nbr] = true;
				parent[nbr] = current;
			}
		}

		free(nbrs);
	}

	free(queue);
	free(chk_vtx);
	free(parent);
	free(path);
	*len = 0;
	return NULL;
}

//Compute the residual flow matrix
// Graph*

// Print an array
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
