#ifndef GRAPH_H
#define GRAPH_H
typedef struct {
	int** adj_mat;
	int num_vtx;
} Graph;

Graph make_graph(int n);
void free_graph(Graph* g);
void print_graph(Graph* g);
void add_capacity(Graph* g, int i, int j, int c);
void randomize_graph(Graph* g, int max);

#endif
