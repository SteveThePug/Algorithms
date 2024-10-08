#include "graph.h"

#include <stdlib.h>
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

// Free the dynamicially allocated graph
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
	int* chk_vtx = calloc(n, sizeof(int)); 
	chk_vtx[u] = 1;
	// Make a stack for what verticies we should explore first and add the start vertex
	int stk_count = 1;
	int* stk = calloc(n, sizeof(int)); 
	stk[0] = u;
	// Allocate a path with at most n verticies
	int* path = malloc(n*sizeof(int));
	int path_len = 0;

	//Begin exploring
	while (stk_count > 0) {
		int current = stk[--stk_count];

		path[path_len++] = current;

		if (current == v) {
			free(stk);
			free(chk_vtx);
			*len = path_len;
			return realloc(path, path_len * sizeof(int));
		}

		int nbr_len;
		int* nbrs = vertex_neighbors(g, current, &nbr_len);

		for (int i=0;i<nbr_len;i++) {
			int nbr = nbrs[i];
			if (!chk_vtx[nbr]) {
				stk[stk_count++] = nbr;
				chk_vtx[nbr] = 1;
			}
		}

		free(nbrs);
	}

	free(stk);
	free(chk_vtx);
	*len = 0;
	return realloc(path, 0);
}

int* bfs_find_path(Graph* g, int u, int v, int* len) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	int* chk_vtx = calloc(n, sizeof(int)); 
	chk_vtx[u] = 1;
	// Make a stack for what verticies we should explore first and add the start vertex
	int que_count = 1;
	int* que = calloc(n, sizeof(int)); 
	que[0] = u;
	// Allocate a path with at most n verticies
	int* path = malloc(n*sizeof(int));
	int path_len = 0;

	free(que);
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
