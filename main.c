#include<stdio.h>
#include<stdlib.h>

#include "graph.h"

int main(int argc, char* argv[]) {
	int n = 10;

	if (argc > 1) {
		n=atoi(argv[1]);
	}

	Graph g = make_graph(n);
	randomize_graph(&g, n);
	print_graph(&g);
	printf("\n");

	int len;
	int* arr = vertex_neighbors(&g, rand()%n, &len);

	int p_len;
	int u = rand()%n;
	int v = rand()%n;
	int* path = dfs_find_path(&g, u, v, &p_len);
	printf("u:%2d, v:%2d\n", u, v);
	print_array(path, p_len);

	free_graph(&g);
	return 0;
}
