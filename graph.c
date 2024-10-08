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
int* dfs_find_path(Graph* g, int u, int v) {
	int n = g->num_vtx;
	// Make a list for checking if we have looked at the vertex
	int* chk_vtx = calloc(n, sizeof(int)); 
	// Make a stack for what verticies we should explore first (-1 = not a vtx)
	int* stk = calloc(n, sizeof(int)); 
	fill_array(stk, n, -1);

	
	
	print_array(stk,n);

	free(stk);
	free(chk_vtx);
	return (int*)NULL;
}

int* bfs_find_path(Graph* g, int u, int v) {
	int n = g->num_vtx;
	// Make a graph for checking if we have looked at a value or not. 1=seen 0=notseen
	int* chk_vtx = calloc(n, sizeof(int)); 
	// Make a queue for what we should explore
	int* que = calloc(n, sizeof(int)); 
	fill_array(que, n, -1);

	free(que);
	free(chk_vtx);
	return (int*)NULL;
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
