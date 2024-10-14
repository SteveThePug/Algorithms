#include<stdio.h>
#include<stdlib.h>

#include "graph.h"
#include "list.h"

int main(int argc, char* argv[]) {
	int n = 10;

	if (argc > 1) {
		n=atoi(argv[1]);
	}

	// Using gdb, you can inspect the values using breakpoints
	// call print_array(int*, n)
	// call print_graph(Graph* g)
	Graph* g = make_graph(n);
	randomize_graph(g, n);

	int len;
	int* arr = vertex_neighbors(g, rand()%n, &len);

	int u = rand()%n;
	int v = rand()%n;
	while (u == v) {
		int v = rand()%n;
	}

	int dfs_len;
	int* dfs_path = dfs_find_path(g, u, v, &dfs_len);
	int bfs_len;
	int* bfs_path = bfs_find_path(g, u, v, &bfs_len);
	free_graph(g);
	free(bfs_path);
	free(dfs_path);

 	List* l = make_list();	
 	push(l, 1);
	push(l, 2);
	push(l, 3);
	push(l, 4);
	enqueue(l, 5);
	enqueue(l, 6);
	reverse_list(l);
	free_list(l);

	return 0;
}
