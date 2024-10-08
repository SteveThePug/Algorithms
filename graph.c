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
		for (int j=0; j<n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

// Adds an edge connecting i->j with capacity c
void add_capacity(Graph *g, int i, int j, int c) {
	g->adj_mat[i][j] = c;
}

//Randomize the capacities of a graph
void randomize_graph(Graph* g, int max) {
	int n = g->num_vtx;
	srand(time(NULL));

	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			g->adj_mat[i][j] = rand() % max;
		}
		g->adj_mat[i][i] = 0;
	}
}
