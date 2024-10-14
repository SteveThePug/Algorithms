#ifndef GRAPH_H
#define GRAPH_H
typedef struct {
	int** adj_mat;
	int num_vtx;
} Graph;

Graph* make_graph(int n);
void free_graph(Graph* g);

void print_graph(Graph* g);

void add_edge(Graph* g, int u, int v, int c);
int* vertex_neighbors(Graph* g, int u, int* len);

void randomize_graph(Graph* g, int max);

int* dfs_find_path(Graph* g, int u, int v, int* len);
int* bfs_find_path(Graph* g, int u, int v, int* len);

void print_array(int* arr, int n);
void fill_array(int* arr, int n, int v);

#endif
